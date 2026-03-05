#pragma once
#include <vector>


namespace zipline
{

class ZipSystem;
class Order;
/**
 * @brief Interface which decides which is next stop - local ordering of a zip system
 * @todo, move logic for ETA here from Actor
 */
class RoutingPolicy
{
public:
  virtual  ~RoutingPolicy() = default;

  virtual Flight PlanRoute(const ZipSystem& korZipsystem, const std::vector<Order>& korOrders, Timestamp launchTime) = 0;
};

}
