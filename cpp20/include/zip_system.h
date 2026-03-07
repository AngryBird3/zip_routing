#pragma  once

#include "common_types.h"

namespace zipline
{
using ZipSystemId = int;
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

  ZipSystem(int id, int capacity, int maxRange, Location position, int speed, Priority priority = Priority::OTHER)
    : id_(id)
    , capacity_(capacity)
    , maxRange_(maxRange)
    , position_(position)
    , priority_(priority)
    , speed_(speed)
  {}

  int GetId() const { return id_; }

  Location GetPosition() const { return position_; }

  void SetPosition(Location position) { position_ = position; }

  Priority GetPriority() const { return priority_; }

  int GetCapacity() const { return capacity_; }

  int GetMaxDistance() const { return maxRange_; }

  int GetSpeed() const { return speed_; }
private:
  int id_{}; ///< ID

  int capacity_{}; ///< how much this zip can carry

  int maxRange_{}; ///< Range. Max distance I can fly

  Location position_{}; ///< Where am I

  Priority priority_{}; ///< I am carrying out these orders

  int speed_{};
  // We could "assign" this to certain Hex to zips
  // So even when they are at Nest, they are allocated
  // to certain hex or location
};
}