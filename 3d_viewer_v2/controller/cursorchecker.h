#ifndef VIEWER_CONTROLLER_CURSORCHECKER_H
#define VIEWER_CONTROLLER_CURSORCHECKER_H

#include <QOpenGLWidget>
#include <QVector4D>

namespace s21 {

/**
 * @brief The CursorChecker class is responsible for checking cursor positions
 * and handling model rotations.
 */
class CursorChecker {
 public:
  /**
   * @brief Constructs a CursorChecker object.
   * @param canvas The QOpenGLWidget representing the canvas.
   */
  CursorChecker(QOpenGLWidget* canvas);

  /**
   * @brief Checks if the cursor is within the canvas area.
   * @param xPressPoint The x-coordinate of the cursor.
   * @param yPressPoint The y-coordinate of the cursor.
   * @return True if the cursor is within the canvas area, false otherwise.
   */
  bool IsCanvasArea(const double xPressPoint, const double yPressPoint);

  /**
   * @brief Calculates the model rotation based on cursor movement.
   * @param coords A QVector4D containing cursor coordinates and rotation
   * sensitivity values.
   */
  void CalculateModelRotation(QVector4D& coords);

  /**
   * @brief Get the current x rotation value.
   * @return The x rotation value.
   */
  double x() const;

  /**
   * @brief Get the current y rotation value.
   * @return The y rotation value.
   */
  double y() const;

  /**
   * @brief Sets the sensetivity value for rotation calculate
   * @param value sensetivity
   */
  void SetSensetivity(const float value);

 private:
  /**
   * @brief Normalizes a real value to integers in the range -1 to 1.
   * @param value A value to normalize.
   * @return Integer value in the range -1 to 1.
   */
  int normalize_(float value);

  QOpenGLWidget* canvas_ = nullptr;

  float x_previous_mouse_ = 0; /**< Previous mouse X coordinate value. >*/
  float y_previous_mouse_ = 0; /**< Previous mouse Y coordinate value. >*/

  double x_value_ = 0; /**< X coordinates of the previous mouse position >*/
  double y_value_ = 0; /**< Y coordinates of the previous mouse position >*/
  double x_sens_ = 1;  /**< X sensitivity >*/
  double y_sens_ = 1;  /**< Y sensitivity >*/
};

}  // namespace s21

#endif  // VIEWER_CONTROLLER_CURSORCHECKER_H
