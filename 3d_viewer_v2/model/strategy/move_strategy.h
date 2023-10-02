#ifndef INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_MOVE_STRATEGY_H_
#define INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_MOVE_STRATEGY_H_

#include <array>

#include "interface_object_transformation_strategy.h"
#include "model/object_3d.h"

namespace s21 {
/**
 * @brief The MoveStrategy class represents a strategy for moving an object.
 */
class MoveStrategy : public IObjectTransformationStrategy {
 public:
  /**
   * @brief Transform the object by moving it using the provided parameters.
   * @param args An array of three float values (dx, dy, dz) representing the
   * movement in each axis.
   */
  void transform(const std::array<float, 3> &args) override;
};

}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_MOVE_STRATEGY_H_
