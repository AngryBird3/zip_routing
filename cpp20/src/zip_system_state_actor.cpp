#include "zip_system_state_actor.h"

namespace zipline {

void ZipSystemStateActor::Assign(Location startingPosition, Flight flight, Timestamp now)
{
  system_.SetPosition(startingPosition);
  float totalDistance = 0.f;
  Location current = system_.GetPosition();  // home base

  for (const auto& order : flight.Orders()) {
    totalDistance += spatialModel_->Distance(current, order.hospital().GetLocation());
    current = order.hospital().GetLocation();
  }

  // Return leg
  totalDistance += spatialModel_.Distance(current, startingPosition);

  Timestamp eta = now + static_cast<Timestamp>(total_distance / system_.speed());

  activeFlight_  = std::move(flight);
  eta_     = eta;
  state_   = ActorState::BUSY;
}

void ZipSystemStateActor::Tick(Timestamp now){
  if (State() == ActorState::FREE) return;
  if (now > eta_) {
    state_ = ActorState::FREE;
    activeFlight_.reset();
  }
}
}