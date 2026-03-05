// Copyright 2021 Zipline International Inc. All rights reserved.

#include  "zip_scheduler.h"

#include "AssignmentPolicy.h"
#include "routing_policy.h"

namespace zipline
{

ZipScheduler::ZipScheduler(const std::vector<ZipSystem> &zips, std::shared_ptr<SpatialModelInterface> spatialModel)
    : spatialModel_(spatialModel)
{
    for (const auto &zip : zips) {
        actors_.push_back(ZipSystemStateActor{zip, spatialModel});
    }
}

void ZipScheduler::QueueOrder(const Order &order)
{
    orderQueue_.push_back(order);
}

std::vector<Flight> ZipScheduler::LaunchFlights(Timestamp current_time)
{
    // 1. Tick all actors first — state transitions happen here
    for (auto& actor : actors_) {
        actor.Tick(current_time);
    }

    std::vector<ZipSystem> availableZips;
    for (const auto& actor : actors_) {
        if (actor.IsFree()) {
            availableZips.push_back(actor.GetSystem());
        }
    }
    // Assignment. No mutex, no multithreading
    auto result =
        assignmentPolicy_->Assign(availableZips, orderQueue_);

    // 3. Re-queue unassigned orders (FIFO preserved)
    orderQueue_ = result.unassignedOrders;

    // 4. Build routes from assignments
    return routePlanner_->PlanRoute(result., result.assignedOrders, current_time);
}
}  // namespace zipline
