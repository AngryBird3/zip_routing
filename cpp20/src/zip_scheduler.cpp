// Copyright 2021 Zipline International Inc. All rights reserved.

#include "zip_scheduler.h"

#include "priority_based_assignment_policy.h"
#include "trivial_routing_policy.h"

namespace zipline
{

ZipScheduler::ZipScheduler(const std::unordered_map<ZipSystemId, ZipSystem>& zips, std::shared_ptr<SpatialModelInterface> spatialModel, Location startingPosition)
    : spatialModel_(spatialModel), startingPosition_(startingPosition)
{
    for (const auto& [id, system] : zips) {
        zips_[id] = std::make_shared<ZipSystem>(system);
        actors_.emplace(id, std::make_shared<ZipSystemStateActor>(system));
    }
    assignmentPolicy_ = std::make_unique<PriorityBasedAssignmentPolicy>(*spatialModel_);
    routePlanner_ = std::make_unique<TrivialRoutingPolicy>();
}

void ZipScheduler::QueueOrder(const Order &order)
{
    orderQueue_.push_back(order);
}

std::vector<Flight> ZipScheduler::LaunchFlights(Timestamp current_time)
{
    // 1. Tick all actors first — state transitions happen here
    for (auto& [zipId, actor] : actors_) {
        actor->Tick(current_time);
    }

    std::vector<std::shared_ptr<ZipSystem>> availableZips;
    for (const auto& [zipId, actor] : actors_) {
        if (actor->IsFree()) {
            availableZips.push_back(actor->GetSystem());
        }
    }
    if (availableZips.empty() || orderQueue_.empty()) {
        return {};
    }
    // Assignment. No mutex, no multithreading
    auto result =
        assignmentPolicy_->Assign(availableZips, orderQueue_);

    // 3. Re-queue unassigned orders (FIFO preserved)
    orderQueue_ = result.unassignedOrders;

    // 4. Build routes (policy sets ETA on flight) and assign
    std::vector<Flight> launchedFlights;
    for (auto& [zipId, orders] : result.assignedOrders) {
        if (orders.empty()) continue;
        auto actor = actors_[zipId];
        Flight flight = routePlanner_->PlanRoute(
            actor->GetSystem(), orders, current_time, startingPosition_, spatialModel_);
        launchedFlights.push_back(flight);
        actor->Assign(startingPosition_, std::move(flight), current_time);
    }

    return launchedFlights;
}
}  // namespace zipline
