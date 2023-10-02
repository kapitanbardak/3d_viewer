#include "save_img_command.h"

namespace s21 {
/**
 * @brief Constructor for the SaveImgCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 */
SaveImgCommand::SaveImgCommand(GlCanvas *canvas) : canvas_(canvas) {
  file_location_ = QString::fromUtf8(Object3D::Instance().GetPath().c_str());
}

/**
 * @brief Execute the image saving command.
 *
 * This method captures the current frame from the GlCanvas and prompts the user
 * to save it as an image file (BMP or JPEG).
 */
void SaveImgCommand::execute() {
  QImage local_frame = canvas_->grabFramebuffer();
  QDir file_dir = QFileInfo(file_location_).absoluteDir();
  QString path = QFileDialog::getSaveFileName(
      canvas_, NULL, file_dir.filePath("name.bmp"), "BMP JPEG (*.bmp *.jpeg)",
      0, QFileDialog::DontUseNativeDialog);
  if (!path.isNull()) local_frame.save(path);
}
}  // namespace s21
