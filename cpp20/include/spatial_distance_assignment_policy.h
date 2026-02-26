#pragma once
#include "AssignmentPolicy.h"
#include "spatial_model.h"

namespace zipline {
/**
 * @brief Uses Spatial distance to assign
 * This is just example, and not implementation to show what can we
 * do with assignment policy.
 * Next could be HexBasedAssignmentPolicy.
 */
class spatial_distance_assignment_policy : public AssignmentPolicy {
public:
  AssignmentResult Assign(const std::vector<ZipSystem> &systems, const std::vector<Order> &orders) const override;
private:
  SpatialModelInterface& orSpatialModel_;
};
}