#pragma once

#include "order.h"


#include <unordered_map>
namespace zipline
{

class ZipSystem;
class Order;

// Yes repeating, lazy
using ZipSystemId = int;

struct AssignmentResult
{
  std::unordered_map<ZipSystemId, std::vector<Order>> assignedOrders; ///< Zip system to list of orders
  std::vector<Order> unassignedOrders; ///< Order we aren't gonna fulfill yet
};

/**
 * @brief Takes care of assigning an order to Zip
 * @details This is interface. play ground to try various things:
 * Assignment can use following things:
 * Geometry:
 *   region/hex/zone
 *   within radius R
 *   same "nest"
 * Joby priority: Say all priority1 goes in same bucket
 * System Load (Zip capacity)
 * Doesn't do: Path, order of delivery
 */
class AssignmentPolicy
{
public:
  virtual ~AssignmentPolicy() = default;

  /**
   * @brief Given list of systems available, assign order to them
   * @param systems Zips
   * @param orders Order
   * @return Map of which zip system will carry which order
   */
  virtual AssignmentResult Assign(const std::vector<ZipSystem> &systems,
      const std::vector<Order> &orders) const = 0;
};

}
