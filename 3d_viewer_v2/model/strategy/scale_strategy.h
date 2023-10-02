#ifndef INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_SCALE_STRATEGY_H_
#define INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_SCALE_STRATEGY_H_

#include "interface_object_transformation_strategy.h"
#include "model/object_3d.h"

namespace s21 {
/**
 * @brief The ScaleStrategy class represents a strategy for scaling an object.
 */
class ScaleStrategy : public IObjectTransformationStrategy {
 public:
  /**
   * @brief Transform the object by scaling it uniformly.
   * @param scale_value The scale factor to be applied to the object.
   */
  void transform(const float scale_value) override;
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_SCALE_STRATEGY_H_
