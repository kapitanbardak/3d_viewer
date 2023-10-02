#ifndef INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_ROTATE_STRATEGY_H_
#define INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_ROTATE_STRATEGY_H_

#include <array>

#include "interface_object_transformation_strategy.h"
#include "model/object_3d.h"

namespace s21 {
/**
 * @brief The RotateStrategy class represents a strategy for rotating an object.
 */
class RotateStrategy : public IObjectTransformationStrategy {
 public:
  /**
   * @brief Transform the object by rotating it using the provided rotation
   * angles.
   * @param args An array of three float values (x, y, z) representing the
   * rotation angles in radians for each axis.
   */
  void transform(const std::array<float, 3> &args) override;
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_ROTATE_STRATEGY_H_
