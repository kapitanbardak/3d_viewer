#ifndef VIEWER_CONTROLLER_COMMANDS_RESET_POSITION_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_RESET_POSITION_COMMAND_H

#include "controller/items_property_controller.h"
#include "core/glcanvas.h"
#include "interface_controller_command.h"
#include "model/interface/data_model.h"

namespace s21 {
/**
 * @brief A command to reset the position of a 3D model.
 */
class ResetPosition : public ICommand {
 public:
  /**
   * @brief Constructs a ResetPosition command.
   * @param model A pointer to the DataModel.
   * @param canvas A pointer to the GlCanvas.
   * @param window A pointer to the Ui_MainWindow.
   */
  ResetPosition(DataModel* model, GlCanvas* canvas,
                ItemsPropertyController* item_controller);

  /**
   * @brief Executes the command, resetting the model's position.
   */
  void execute() override;

 private:
  DataModel* model_ = nullptr;  ///< Pointer to the DataModel.
  GlCanvas* canvas_ = nullptr;  ///< Pointer to the GlCanvas.
  ItemsPropertyController* item_controller_ = nullptr;
};
}  // namespace s21
#endif  // RESET_POSITION_COMMAND_H
