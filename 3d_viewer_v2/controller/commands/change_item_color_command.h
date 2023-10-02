#ifndef VIEWER_CONTROLLER_COMMANDS_CHANGE_ITEM_COLOR_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_CHANGE_ITEM_COLOR_COMMAND_H

#include <QColorDialog>

#include "controller/items_property_controller.h"
#include "core/glcanvas.h"
#include "interface_controller_command.h"

namespace s21 {
/**
 * @brief Command for changing the color of an item on the canvas.
 */
class ChangeItemColorCommand : public ICommand {
 public:
  /**
   * @brief Constructor for creating a command to change the color of an item.
   * @param canvas A pointer to the GlCanvas object.
   * @param mode The mode of color change (e.g., kBackground, kRibs, or
   * kVertex).
   * @param ui_changer The UI controller.
   */
  ChangeItemColorCommand(GlCanvas *canvas, FunctionsMode,
                         ItemsPropertyController *);

  /**
   * @brief Executes the command to change the color of an item.
   */
  void execute() override;

 private:
  GlCanvas *canvas_ = nullptr; /**< A pointer to the GlCanvas object. */
  FunctionsMode mode_; /**< The mode of color change (e.g., kBackground, kRibs,
                          or kVertex). */
  ItemsPropertyController *ui_changer_; /**<  The UI controller.  */
};
}  // namespace s21
#endif  // VIEWER_CONTROLLER_COMMANDS_CHANGE_ITEM_COLOR_COMMAND_H
