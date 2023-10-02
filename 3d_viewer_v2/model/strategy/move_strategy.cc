#include "move_strategy.h"

namespace s21 {
/**
 * @brief Apply a translation transformation to the 3D object.
 *
 * @param args An array containing the translation values along the X, Y, and Z
 * axes.
 */
void MoveStrategy::transform(const std::array<float, 3> &args) {
  float dx = args[0];
  float dy = args[1];
  float dz = args[2];
  if (dx || dy || dz) {
    for (size_t i = 0; i < Object3D::Instance().GetPointsAmount(); i += 3) {
      Object3D::Instance().Points().at(i) += dx;
      Object3D::Instance().Points().at(i + 1) += dy;
      Object3D::Instance().Points().at(i + 2) += dz;
    }
  }
}
}  // namespace s21
