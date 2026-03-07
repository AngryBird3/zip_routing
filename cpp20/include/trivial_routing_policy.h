#pragma once
#include "flight.h"
#include "routing_policy.h"
#include "util.h"

namespace zipline {
class TrivialRoutingPolicy : public RoutingPolicy{
public:
  Flight PlanRoute(std::shared_ptr<ZipSystem> system,
                   const std::vector<Order>& orders,
                   Timestamp launchTime,
                   Location startingPosition,
                   std::shared_ptr<SpatialModelInterface> spatialModel) override;
};
}