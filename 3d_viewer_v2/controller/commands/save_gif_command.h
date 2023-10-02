#ifndef INC_3DVIEWER_V2_0_SRC_3D_VIEWER_V2_CONTROLLER_COMMANDS_SAVE_GIF_COMMAND_H_
#define INC_3DVIEWER_V2_0_SRC_3D_VIEWER_V2_CONTROLLER_COMMANDS_SAVE_GIF_COMMAND_H_

#include <QDir>
#include <QFileDialog>
#include <QImage>
#include <QObject>
#include <QString>
#include <QTimer>

#include "controller/items_property_controller.h"
#include "core/glcanvas.h"
#include "interface_controller_command.h"
#include "model/object_3d.h"
#include "qgifimage.h"

namespace s21 {
/**
 * @brief A command to save a GIF animation from the GlCanvas.
 */
class SaveGifCommand : public QObject, public ICommand {
  Q_OBJECT
 public:
  /**
   * @brief Constructs a SaveGifCommand.
   * @param canvas A pointer to the GlCanvas.
   * @param canvas A pointer to the GlCanvas.
   */
  SaveGifCommand(GlCanvas* canvas, ItemsPropertyController* item_controller);
  ~SaveGifCommand();

  /**
   * @brief Executes the command, capturing frames and saving as a GIF.
   */
  void execute() override;

 private:
  int frames_number_; /**< The number of frames captured for the GIF. */
  GlCanvas* canvas_ = nullptr; /**< Pointer to the GlCanvas. */
  QGifImage* gif_image_;       /**< The GIF image object. */
  QString file_location_; /**< The file location where the GIF will be saved. */
  QTimer* watch_dog_;     /**< A timer to control frame capturing. */
  ItemsPropertyController* item_controller_; /**< A UI controller. */

 private slots:
  /**
   * @brief Slot to add a frame to the GIF image.
   */
  void AddFrameToGif_();
};

}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_3D_VIEWER_V2_CONTROLLER_COMMANDS_SAVE_GIF_COMMAND_H_
