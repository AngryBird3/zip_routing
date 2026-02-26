#pragma once
#include "flight.h"
#include "routing_policy.h"
#include "util.h"

namespace zipline {
class TrivialRoutingPolicy : public RoutingPolicy{
public:
  std::vector<Flight> PlanRoute(const ZipSystem& korZipsystem, const std::vector<Order>& korOrders, Timestamp launchTime) override;
};
}