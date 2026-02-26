#pragma once
#include <vector>


namespace zipline
{

class ZipSystem;
class Order;
/**
 * @brief Interface which decides which is next stop - local ordering of a zip system
 *
 */
class RoutingPolicy
{
public:
  virtual  ~RoutingPolicy() = default;

  virtual std::vector<Flight> PlanRoute(const ZipSystem& korZipsystem, const std::vector<Order>& korOrders, Timestamp launchTime) = 0;
};

}
