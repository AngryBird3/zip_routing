#pragma once
#include <optional>
#include "flight.h"
#include "util.h"
#include "zip_system.h"

namespace zipline {
/**
 * Dumb state holder: stores system, current flight, and state. Ticks until flight ETA then resets.
 */
class ZipSystemStateActor {
public:
  enum class ActorState { FREE, BUSY };
  explicit ZipSystemStateActor(ZipSystem system)
    : system_(std::make_shared<ZipSystem>(system)) {}

  /**
   * Update
   */
  void Tick(Timestamp now);

  /**
   * Assign System for state maintance
   * @param startingPosition
   * @param flight
   * @param now
   */
  void Assign(Location startingPosition, Flight flight, Timestamp now);

  bool IsFree() const { return state_ == ActorState::FREE; }

  ActorState State() const { return state_; }

  // Expose underlying system for AssignmentPolicy queries
  const std::shared_ptr<ZipSystem> GetSystem() const { return system_; }

private:
  void Reset();

  std::shared_ptr<ZipSystem> system_;
  ActorState state_{ActorState::FREE};
  std::optional<Flight> flight_;
};
}