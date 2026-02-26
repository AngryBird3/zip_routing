#pragma  once

#include "common_types.h"

namespace zipline
{
// This is to represent a Zipline robot/drone
class ZipSystem {
public:
  /// @brief Zip system' priority
  /// @note For now we are tying zipsystem to priority for priority based assigment
  /// Yep I need something simple asap for now
  enum class Priority {
     OTHER = 0,
     EMERGENCY = 1,
  };

  ZipSystem(int id, int capacity, int maxDistance, Location position, Priority priority = Priority::OTHER)
    : id_(id)
    , capacity_(capacity)
    , maxDistance_(maxDistance)
    , position_(position)
    , priority_(priority)
  {}

  int GetId() const { return id_; }

  Location GetPosition() const { return position_; }

  Priority GetPriority() const { return priority_; }

  int GetCapacity() const { return capacity_; }

  int GetMaxDistance() const { return maxDistance_; }

private:
  int id_{}; ///< ID

  int capacity_{}; ///< how much this zip can carry

  int maxDistance_{}; ///< Range. Max distance I can fly

  Location position_{}; ///< Where am I

  Priority priority_{}; ///< I am carrying out these orders

  // We could "assign" this to certain Hex to zips
  // So even when they are at Nest, they are allocated
  // to certain hex or location
};
}