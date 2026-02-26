// Copyright 2021 Zipline International Inc. All rights reserved.

#include  "zip_scheduler.h"

#include "AssignmentPolicy.h"
#include "routing_policy.h"

namespace zipline
{
void ZipScheduler::QueueOrder(const Order &order)
{
    orderQueue_.push_back(order);
}

std::vector<Flight> ZipScheduler::LaunchFlights(Timestamp current_time)
{
    // Assignment. No mutex, no multithreading
    auto result =
        assignmentPolicy_->Assign(zips_, orderQueue_);

    // 3. Re-queue unassigned orders (FIFO preserved)
    orderQueue_ = result.unassignedOrders;

    // 4. Build routes from assignments
    return routePlanner_->PlanRoute(zips_, result.assignedOrders);
}
}  // namespace zipline
