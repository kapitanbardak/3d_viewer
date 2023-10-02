#include "cursorchecker.h"

namespace s21 {
/**
 * @brief Constructor for the CursorChecker class.
 */
CursorChecker::CursorChecker(QOpenGLWidget* canvas) : canvas_(canvas){};

/**
 * @brief Calculate model rotation based on cursor movement.
 *
 * @param coords Vector containing cursor and rotation values.
 */
void CursorChecker::CalculateModelRotation(QVector4D& coords) {
  double x_current = coords[0], y_current = coords[1];
  double x_delta = x_current - x_previous_mouse_,
         y_delta = y_current - y_previous_mouse_;

  x_previous_mouse_ = x_current;
  y_previous_mouse_ = y_current;

  x_value_ = coords[2] + y_sens_ * normalize_(y_delta);
  y_value_ = coords[3] + x_sens_ * normalize_(x_delta);
}

/**
 * @brief Check if the cursor is within the canvas area.
 *
 * @param canvas Reference to the QOpenGLWidget representing the canvas.
 * @param x_press_point X-coordinate of the cursor.
 * @param y_press_point Y-coordinate of the cursor.
 * @return true if the cursor is within the canvas area, false otherwise.
 */
bool CursorChecker::IsCanvasArea(const double x_press_point,
                                 const double y_press_point) {
  GLfloat width = canvas_->width(), height = canvas_->height();

  float x_gl_coordinates = canvas_->pos().x(),
        y_gl_coordinates = canvas_->pos().y();

  return ((x_press_point >= x_gl_coordinates &&
           x_press_point <= (x_gl_coordinates + width)) &&
          (y_press_point >= y_gl_coordinates &&
           (y_press_point <= y_gl_coordinates + height)));
}

/**
 * @brief Get the current x-value.
 *
 * @return The current x-value.
 */
double CursorChecker::x() const { return x_value_; }

/**
 * @brief Get the current y-value.
 *
 * @return The current y-value.
 */
double CursorChecker::y() const { return y_value_; }

/**
 * @brief Normalizes a real value to integers in the range -1 to 1.
 * @param value A value to normalize.
 * @return Integer value in the range -1 to 1.
 */
int CursorChecker::normalize_(float value) {
  if (value > 0)
    return 1;
  else if (value == 0)
    return 0;
  else
    return -1;
}

void CursorChecker::SetSensetivity(const float value) {
  x_sens_ = value;
  y_sens_ = value;
}
}  // namespace s21
