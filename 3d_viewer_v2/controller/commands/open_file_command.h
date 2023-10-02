#ifndef VIEWER_CONTROLLER_COMMANDS_OPEN_FILE_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_OPEN_FILE_COMMAND_H

#include <QFileDialog>

#include "controller/items_property_controller.h"
#include "core/glcanvas.h"
#include "interface_controller_command.h"
#include "model/interface/data_model.h"

namespace s21 {
/**
 * @brief A command for opening a 3D model file.
 */
class OpenFileCommand : public ICommand {
 public:
  /**
   * @brief Constructs an OpenFileCommand.
   * @param canvas A pointer to the GlCanvas.
   * @param object A pointer to the DataModel.
   * @param item_controller A pointer to the ItemsPropertyController.
   */
  OpenFileCommand(GlCanvas* canvas, DataModel* object,
                  ItemsPropertyController* item_controller);

  /**
   * @brief Executes the command, loading the specified 3D model file.
   */
  void execute() override;

 private:
  GlCanvas* canvas_ = nullptr;   ///< Pointer to the GlCanvas.
  DataModel* object_ = nullptr;  ///< Pointer to the DataModel.
  ItemsPropertyController* item_controller_ =
      nullptr;        /** < Pointer to the ItemsPropertyController. > */
  std::string path_;  ///< The path to the 3D model file to open.
};
}  // namespace s21
#endif  // VIEWER_CONTROLLER_COMMANDS_OPEN_FILE_COMMAND_H
