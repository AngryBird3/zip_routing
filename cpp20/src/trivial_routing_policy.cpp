#include "trivial_routing_policy.h"

#include "order.h"
#include "zip_system.h"

namespace zipline {
Flight TrivialRoutingPolicy::PlanRoute(
    std::shared_ptr<ZipSystem> system,
    const std::vector<Order>& orders,
    Timestamp launchTime,
    Location startingPosition,
    std::shared_ptr<SpatialModelInterface> spatialModel)
{
  Flight flight(launchTime, orders);
  if (orders.empty()) {
    flight.setEta(launchTime);
    return flight;
  }
  float totalDistance = 0.f;
  Location current = startingPosition;
  for (const auto& order : flight.Orders()) {
    totalDistance += spatialModel->Distance(current, order.hospital().GetLocation());
    current = order.hospital().GetLocation();
  }
  totalDistance += spatialModel->Distance(current, startingPosition);
  flight.setEta(launchTime + static_cast<Timestamp>(totalDistance / system->GetSpeed()));
  return flight;
}
}