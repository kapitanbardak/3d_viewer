#include "rotate_strategy.h"

namespace s21 {
/**
 * @brief Apply a rotation transformation to the 3D object.
 *
 * @param args An array containing the rotation angles around the X, Y, and Z
 * axes.
 */
void RotateStrategy::transform(const std::array<float, 3> &args) {
  float x = args[0];
  float y = args[1];
  float z = args[2];

  float cos_a = cos(x);
  float sin_a = sin(x);

  float cos_b = cos(y);
  float sin_b = sin(y);

  float cos_y = cos(z);
  float sin_y = sin(z);

  for (size_t i = 0; i < Object3D::Instance().GetPointsAmount(); i += 3) {
    float x = Object3D::Instance().Points().at(i);
    float y = Object3D::Instance().Points().at(i + 1);
    float z = Object3D::Instance().Points().at(i + 2);

    Object3D::Instance().Points().at(i) =
        x * cos_b * cos_y - y * sin_y * cos_b + z * sin_b;
    Object3D::Instance().Points().at(i + 1) =
        x * (sin_a * sin_b * cos_y + sin_y * cos_a) +
        y * (-sin_a * sin_b * sin_y + cos_a * cos_y) - z * sin_a * cos_b;
    Object3D::Instance().Points().at(i + 2) =
        x * (sin_a * sin_y - sin_b * cos_a * cos_y) +
        y * (sin_a * cos_y + sin_b * sin_y * cos_a) + z * cos_a * cos_b;
  }
}
}  // namespace s21
