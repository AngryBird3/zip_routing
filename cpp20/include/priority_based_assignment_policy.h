#pragma once

#include "AssignmentPolicy.h"
#include "spatial_model_interface.h"

namespace zipline {
class PriorityBasedAssignmentPolicy : public AssignmentPolicy
{
public:
  explicit PriorityBasedAssignmentPolicy(SpatialModelInterface& spatialModel) : spatialModel_(spatialModel) {}

  /**
   * @brief It does basic assignment. Assign to zip if:
   * 1. load(zip) > CAPACITY (max number of packages)
   * 2. priority compatible. Remember each zip has priority
   * 3. est_distance[zip] + incremental_distance > MAX_TOTAL_DISTANCE
   * @param systems
   * @param orders
   * @return
   */
  AssignmentResult Assign(std::vector<std::shared_ptr<ZipSystem>> systems,
     const std::vector<Order> &orders) const override;

private:
  /**
   * Matching priority
   * @param sys Zip
   * @param order Order
   * @return true if emergency order has emergency serving system or Other order and other priorty
   */
  static bool canHandle(std::shared_ptr<ZipSystem> sys, const Order& order) ;

  SpatialModelInterface& spatialModel_; ///< Spatial model to estimate distance
};
}