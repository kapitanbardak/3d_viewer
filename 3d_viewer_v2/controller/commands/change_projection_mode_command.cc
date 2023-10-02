#include "change_projection_mode_command.h"

namespace s21 {
/**
 * @brief Constructor for the ChangeProjectionModeCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 * @param mode The mode in which to change the projection.
 */
ChangeProjectionModeCommand::ChangeProjectionModeCommand(
    GlCanvas* canvas, const ProjectionType mode,
    ItemsPropertyController* view_controller)
    : canvas_(canvas), mode_(mode), view_controller_(view_controller) {}

/**
 * @brief Execute the projection mode change command.
 *
 * This method applies the new projection mode to the GlCanvas object and
 * triggers a repaint.
 */
void ChangeProjectionModeCommand::execute() {
  canvas_->InitProjectionParameters(mode_);
  view_controller_->SetProjectionButton();
  canvas_->repaint();
}

}  // namespace s21
