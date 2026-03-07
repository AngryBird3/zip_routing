#pragma once
#include <memory>
#include <vector>

#include "common_types.h"
#include "flight.h"
#include "spatial_model_interface.h"
#include "util.h"

namespace zipline {

class ZipSystem;
class Order;

/**
 * @brief Plans route for a zip (ordering of stops) and sets ETA on the returned Flight.
 */
class RoutingPolicy {
public:
  virtual ~RoutingPolicy() = default;

  virtual Flight PlanRoute(std::shared_ptr<ZipSystem> system,
                           const std::vector<Order>& orders,
                           Timestamp launchTime,
                           Location startingPosition,
                           std::shared_ptr<SpatialModelInterface> spatialModel) = 0;
};

}
