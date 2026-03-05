// Copyright 2021 Zipline International Inc. All rights reserved.
#pragma once

#include <vector>

#include "flight.h"
#include "order.h"
#include "util.h"
#include "zip_system_state_actor.h"

namespace zipline {
class RoutingPolicy;}namespace zipline
{
class AssignmentPolicy;
class ZipSystem;

/// \brief assumes this has two zips at least
class ZipScheduler
{
public:
    ZipScheduler(const std::vector<ZipSystem>& zips, std::shared_ptr<SpatialModelInterface> spatialModel);

    // Add an order to the queue to potentially launch at the next time LaunchFlights is called.
    void QueueOrder(const Order &order);

    // Returns an ordered list of flights to launch.
    std::vector<Flight> LaunchFlights(Timestamp current_time);

    void Tick(Timestamp now);
private:
    const ZipSystem zips_{}; ///< ALL zip
    std::vector<Order> orderQueue_{}; ///< Current order
    std::unique_ptr<AssignmentPolicy> assignmentPolicy_{}; ///< Assigning order to zip
    // should use std::mutex to protect zips_ if it was multithreaded
    std::unique_ptr<RoutingPolicy> routePlanner_{}; ///< Once assigned, plan which dest to hit first
    std::vector<ZipSystemStateActor>  actors_{};
    std::shared_ptr<SpatialModelInterface> spatialModel_{};
};

}  // namespace zipline
