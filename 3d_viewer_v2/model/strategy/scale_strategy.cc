#include "scale_strategy.h"

namespace s21 {
/**
 * @brief Apply a scaling transformation to the 3D object.
 *
 * @param scale_value The scaling factor.
 */
void ScaleStrategy::transform(const float scale_value) {
  if (scale_value > 0) {
    for (size_t i = 0; i < Object3D::Instance().GetPointsAmount(); ++i) {
      Object3D::Instance().Points().at(i) *= scale_value;
    }
  }
}
}  // namespace s21
