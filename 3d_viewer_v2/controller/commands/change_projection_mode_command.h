#ifndef VIEWER_CONTROLLER_COMMANDS_CHANGE_PROJECTION_MODE_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_CHANGE_PROJECTION_MODE_COMMAND_H

#include <string.h>

#include "controller/items_property_controller.h"
#include "core/glcanvas.h"
#include "interface_controller_command.h"

namespace s21 {
/**
 * @brief Command for changing the projection mode of an item on the canvas.
 */
class ChangeProjectionModeCommand : public ICommand {
 public:
  /**
   * @brief Constructor for creating a command to change the projection mode of
   * an item.
   * @param canvas A pointer to the GlCanvas object.
   * @param mode The mode of projection change.
   * @param view_controller The controller of the UI.
   */
  ChangeProjectionModeCommand(GlCanvas* canvas, const ProjectionType mode,
                              ItemsPropertyController* view_controller);

  /**
   * @brief Executes the command to change the projection mode of an item.
   */
  void execute() override;

 private:
  GlCanvas* canvas_;    /**< A pointer to the GlCanvas object. */
  ProjectionType mode_; /**< The mode of projection mode change. */
  ItemsPropertyController* view_controller_; /**< The controller of the UI. */
};
}  // namespace s21
#endif  // VIEWER_CONTROLLER_COMMANDS_CHANGE_PROJECTION_MODE_COMMAND_H
