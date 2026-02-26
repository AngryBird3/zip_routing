#pragma once
#include <cstdint>
#include <utility>

namespace zipline
{
using lattitude_t = double;
using longitude_t = double;
using Location = std::pair<lattitude_t, longitude_t>;

enum class FlightState {
  IDLE = 0,
  ENROUTE = 1,
};
}