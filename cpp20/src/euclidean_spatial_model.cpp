#include "euclidean_spatial_model.h"
#include <cmath>

namespace zipline {

float EuclideanSpatialModel::Distance(Location from, Location to)
{
  const double dlat = to.first - from.first;
  const double dlon = to.second - from.second;
  return static_cast<float>(std::sqrt(dlat * dlat + dlon * dlon));
}

}  // namespace zipline
