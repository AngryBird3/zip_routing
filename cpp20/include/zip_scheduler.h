// Copyright 2021 Zipline International Inc. All rights reserved.
#pragma once

#include <unordered_map>
#include <vector>

#include "common_types.h"
#include "flight.h"
#include "order.h"
#include "spatial_model_interface.h"
#include "util.h"
#include "zip_system.h"
#include "zip_system_state_actor.h"
#include "AssignmentPolicy.h"
#include "routing_policy.h"

namespace zipline {

/// \brief assumes this has two zips at least
class ZipScheduler
{
public:
    ZipScheduler(const std::unordered_map<ZipSystemId, ZipSystem>& zips, std::shared_ptr<SpatialModelInterface> spatialModel, Location startingPosition = {0, 0});

    // Add an order to the queue to potentially launch at the next time LaunchFlights is called.
    void QueueOrder(const Order &order);

    // Returns an ordered list of flights to launch.
    std::vector<Flight> LaunchFlights(Timestamp current_time);

    void Tick(Timestamp now);
private:
    std::unordered_map<ZipSystemId, std::shared_ptr<ZipSystem>> zips_{}; ///< ALL zip
    std::vector<Order> orderQueue_{}; ///< Current order
    std::unique_ptr<AssignmentPolicy> assignmentPolicy_{}; ///< Assigning order to zip
    std::unique_ptr<RoutingPolicy> routePlanner_{}; ///< Once assigned, plan which dest to hit first
    std::unordered_map<ZipSystemId, std::shared_ptr<ZipSystemStateActor>> actors_{};
    std::shared_ptr<SpatialModelInterface> spatialModel_{};
    Location startingPosition_{};
};

}  // namespace zipline
