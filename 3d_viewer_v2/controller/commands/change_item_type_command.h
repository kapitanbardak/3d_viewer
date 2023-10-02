#ifndef VIEWER_CONTROLLER_COMMANDS_CHANGE_ITEM_TYPE_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_CHANGE_ITEM_TYPE_COMMAND_H

#include "controller/items_property_controller.h"
#include "core/glcanvas.h"
#include "interface_controller_command.h"

namespace s21 {
/**
 * @brief Command for changing the type of an item (e.g., vertex or ribs) on the
 * canvas.
 */
class ChangeItemTypeCommand : public ICommand {
 public:
  /**
   * @brief Constructor for creating a command to change the type of an item.
   * @param canvas A pointer to the GlCanvas object.
   * @param controller A pointer to the ItemsPropertyController object.
   * @param mode The mode of item type change (e.g., kVertex or kRibs).
   */
  ChangeItemTypeCommand(GlCanvas* canvas, ItemsPropertyController* controller,
                        FunctionsMode mode);

  /**
   * @brief Executes the command to change the type of an item.
   */
  void execute() override;

 private:
  GlCanvas* canvas_ = nullptr; /**< A pointer to the GlCanvas object. */
  ItemsPropertyController* item_controller_ =
      nullptr; /**< A pointer to the ItemsPropertyController object. >*/
  FunctionsMode
      mode_; /**< The mode of item type change (e.g., "vertex" or "ribs"). */
};

}  // namespace s21
#endif  // VIEWER_CONTROLLER_COMMANDS_CHANGE_ITEM_TYPE_COMMAND_H
