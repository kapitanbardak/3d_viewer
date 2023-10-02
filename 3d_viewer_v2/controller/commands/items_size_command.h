#ifndef VIEWER_CONTROLLER_COMMANDS_ITEMS_SIZE_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_ITEMS_SIZE_COMMAND_H

#include "core/glcanvas.h"
#include "interface_controller_command.h"

namespace s21 {
/**
 * @brief A command for changing the size of items in the canvas.
 */
class ItemsSizeCommand : public ICommand {
 public:
  /**
   * @brief Constructs an ItemsSizeCommand.
   * @param canvas A pointer to the GlCanvas.
   * @param mode The mode specifying which items' size to change (e.g., kVertex
   * or kRibs).
   * @param size The new size value to set.
   */
  ItemsSizeCommand(GlCanvas* canvas, FunctionsMode mode, float size);

  /**
   * @brief Executes the command, changing the size of the specified items.
   */
  void execute() override;

 private:
  GlCanvas* canvas_ = nullptr;  ///< Pointer to the GlCanvas.
  FunctionsMode mode_;  ///< The mode specifying which items' size to change.
  float size_ = 0;      ///< The new size value to set.
};
}  // namespace s21
#endif  // VIEWER_CONTROLLER_COMMANDS_ITEMS_SIZE_COMMAND_H
