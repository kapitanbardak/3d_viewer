#include "reset_position_command.h"

namespace s21 {
/**
 * @brief Constructor for the ResetPosition class.
 *
 * @param model Pointer to the DataModel object.
 * @param canvas Pointer to the GlCanvas object.
 * @param window Pointer to the application's main window.
 */
ResetPosition::ResetPosition(DataModel* model, GlCanvas* canvas,
                             ItemsPropertyController* item_contorller)
    : model_(model), canvas_(canvas), item_controller_(item_contorller) {}

/**
 * @brief Execute the reset position command.
 *
 * This method resets the position of the 3D model, initializes the GlCanvas
 * with the updated data, and resets the values in the user interface input
 * boxes. It then triggers a repaint of the canvas.
 */
void ResetPosition::execute() {
  model_->ResetModelPosition();
  item_controller_->ResetBoxesValues();
  canvas_->InitializeArrays(model_->GetVertexArray(),
                            model_->GetIndicesArray());
  canvas_->repaint();
}
}  // namespace s21
