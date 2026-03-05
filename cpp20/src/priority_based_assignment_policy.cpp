#include "priority_based_assignment_policy.h"


#include "AssignmentPolicy.h"

#include "zip_system.h"

namespace zipline {

AssignmentResult PriorityBasedAssignmentPolicy::Assign(const std::vector<ZipSystem> &systems,
    const std::vector<Order> &orders) const
{
    AssignmentResult result;

    // Per-system bookkeeping
    std::unordered_map<int, std::size_t> load;
    std::unordered_map<int, double> estimatedDistance;

    for (const auto& sys : systems) {
        load[sys.GetId()] = 0;
        estimatedDistance[sys.GetId()] = 0.0;
    }

    // FCFS: assume orders already sorted by received_time
    for (const auto& order : orders) {
        bool assigned = false;

        for (const auto& sys : systems) {

            // Priority compatibility
            if (!canHandle(sys, order))
                continue;

            // Capacity check
            if (load[sys.GetId()] >= sys.GetCapacity())
                continue;

            // Distance estimate (incremental)
            double inc =
                spatialModel_.Distance(sys.GetPosition(), order.hospital());

            if (estimatedDistance[sys.GetId()] + inc > sys.GetMaxDistance())
                continue;

            // Assign
            result.assignedOrders[sys.GetId()].push_back(order);
            load[sys.GetId()]++;
            estimatedDistance[sys.GetId()] += inc;
            assigned = true;
            break;
        }

        if (!assigned) {
            result.unassignedOrders.push_back(order);
        }
    }

    return result;
}

bool PriorityBasedAssignmentPolicy::canHandle(const ZipSystem &system, const Order &order) {
    if (order.priority() == Order::Priority::kEmergency && system.GetPriority() == ZipSystem::Priority::EMERGENCY)
        return true;
    if (order.priority() == Order::Priority::kResupply && system.GetPriority() == ZipSystem::Priority::OTHER)
        return true;
    return true;

}

}