#pragma once

#include "common_types.h"
#include "spatial_model_interface.h"

namespace zipline {

/// Simple Euclidean distance in (latitude, longitude) space.
class EuclideanSpatialModel : public SpatialModelInterface
{
public:
  float Distance(Location from, Location to) override;
};

}  // namespace zipline
