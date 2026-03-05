#pragma once
#include "flight.h"
#include "spatial_model_interface.h"
#include "util.h"
#include "zip_system.h"

namespace zipline {
/**
 * Could be derived from Actor. Responsible for managing ticking/ Updating based on time
 * I don't like having to use SpatialModelInterface to calculate ETA. I think
 * something else should own it and this Actor can take ETA when assign, but for
 * now going with this
 */
class ZipSystemStateActor {
public:
  enum class ActorState { FREE, BUSY };
  explicit ZipSystemStateActor(ZipSystem system,
        std::shared_ptr<SpatialModelInterface> spatialModel)
    : system_(std::move(system)), spatialModel_(spatialModel) {}

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
  const ZipSystem& GetSystem() const { return system_; }

private:
  ZipSystem          system_;
  ActorState      state_{ActorState::FREE};
  std::optional<Flight> activeFlight_;
  std::shared_ptr<SpatialModelInterface> spatialModel_{nullptr};
  Timestamp eta_{};
};
}