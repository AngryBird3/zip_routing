#include "zip_system_state_actor.h"

namespace zipline {

void ZipSystemStateActor::Assign(Location startingPosition, Flight flight, Timestamp /*now*/)
{
  system_->SetPosition(startingPosition);
  flight_ = std::move(flight);
  state_ = ActorState::BUSY;
}

void ZipSystemStateActor::Tick(Timestamp now)
{
  if (State() == ActorState::FREE) return;
  if (now >= flight_->eta()) {
    Reset();
  }
}

void ZipSystemStateActor::Reset()
{
  state_ = ActorState::FREE;
  flight_.reset();
}
}