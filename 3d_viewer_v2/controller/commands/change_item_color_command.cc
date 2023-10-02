#include "change_item_color_command.h"

namespace s21 {
/**
 * @brief Constructor for the ChangeItemColorCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 * @param color New color to be applied.
 * @param mode The mode in which to change the color.
 */
ChangeItemColorCommand::ChangeItemColorCommand(
    GlCanvas* canvas, FunctionsMode mode, ItemsPropertyController* ui_changer)
    : canvas_(canvas), mode_(mode), ui_changer_(ui_changer) {}

/**
 * @brief Execute the color change command.
 *
 * This method applies the new color to the GlCanvas object and triggers a
 * repaint.
 */
void ChangeItemColorCommand::execute() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) canvas_->SetColor(color, mode_);
  ui_changer_->SetButtonIcons();
  canvas_->repaint();
}
}  // namespace s21
