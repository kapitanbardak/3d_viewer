#ifndef INC_3DVIEWER_V2_0_SRC_3D_VIEWER_V2_CONTROLLER_COMMANDS_SAVE_IMG_COMMAND_H_
#define INC_3DVIEWER_V2_0_SRC_3D_VIEWER_V2_CONTROLLER_COMMANDS_SAVE_IMG_COMMAND_H_

#include <QDir>
#include <QFileDialog>
#include <QImage>
#include <QString>

#include "core/glcanvas.h"
#include "interface_controller_command.h"
#include "model/object_3d.h"

namespace s21 {
/**
 * @brief A command to save an image snapshot from the GlCanvas.
 */
class SaveImgCommand : public ICommand {
 public:
  /**
   * @brief Constructs a SaveImgCommand.
   * @param canvas A pointer to the GlCanvas.
   */
  SaveImgCommand(GlCanvas *canvas);

  /**
   * @brief Executes the command, capturing and saving the image.
   */
  void execute() override;

 private:
  GlCanvas *canvas_ = nullptr; /**< Pointer to the GlCanvas. */
  QString
      file_location_; /**< The file location where the image will be saved. */
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_3D_VIEWER_V2_CONTROLLER_COMMANDS_SAVE_IMG_COMMAND_H_
