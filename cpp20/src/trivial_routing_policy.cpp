#include "trivial_routing_policy.h"

namespace zipline {
std::vector<Flight> TrivialRoutingPolicy::PlanRoute(
      const ZipSystem& system,
      const std::vector<Order>& orders,
      Timestamp launchTime)
{
  if (orders.empty()) {
    return {};
  }

  Flight flight;
  flight.launch_time_ = launchTime;
  flight.orders_ = orders;

  return { flight };
}
}