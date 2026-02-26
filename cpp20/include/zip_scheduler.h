// Copyright 2021 Zipline International Inc. All rights reserved.
#pragma once

#include <vector>

#include "flight.h"
#include "order.h"
#include "util.h"

namespace zipline {
class RoutingPolicy;}namespace zipline
{
class AssignmentPolicy;
class ZipSystem;

/// \brief assumes this has two zips at least
class ZipScheduler
{
public:
    ZipScheduler(const std::vector<ZipSystem>& zips);

    // Add an order to the queue to potentially launch at the next time LaunchFlights is called.
    void QueueOrder(const Order &order);

    // Returns an ordered list of flights to launch.
    std::vector<Flight> LaunchFlights(Timestamp current_time);
private:
    std::vector<ZipSystem> zips_; ///< ALL zip
    std::vector<Order> orderQueue_; ///< Current order
    std::unique_ptr<AssignmentPolicy> assignmentPolicy_; ///< Assigning order to zip
    // should use std::mutex to protect zips_ if it was multithreaded
    std::unique_ptr<RoutingPolicy> routePlanner_; ///< Once assigned, plan which dest to hit first
};

}  // namespace zipline
