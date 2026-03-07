#pragma once

namespace zipline {
class SpatialModelInterface
{
public:
  virtual float Distance(Location from, Location to) = 0;
  // List<Location> Neighbors(Location a);
};
}