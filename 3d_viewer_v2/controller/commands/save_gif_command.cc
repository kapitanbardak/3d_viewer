#include "save_gif_command.h"

namespace s21 {
/**
 * @brief Constructor for the SaveGifCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 */
SaveGifCommand::SaveGifCommand(GlCanvas* canvas,
                               ItemsPropertyController* item_controller)
    : frames_number_(0),
      canvas_(canvas),
      gif_image_(new QGifImage),
      item_controller_(item_controller) {
  file_location_ = QString::fromUtf8(Object3D::Instance().GetPath().c_str());
}

/**
 * @brief Add a frame to the GIF image.
 *
 * This method adds a frame to the GIF image being created. When a specified
 * number of frames is reached (50 in this case), it stops the timer and prompts
 * the user to save the GIF image.
 */
void SaveGifCommand::AddFrameToGif_() {
  frames_number_++;
  item_controller_->SetRecordProgressBar(
      static_cast<int>(100 * frames_number_ / 50.0));
  QImage local_frame = canvas_->grabFramebuffer();
  local_frame = local_frame.scaled(640, 480);
  gif_image_->addFrame(local_frame, 100);
  if (frames_number_ == 50) {
    item_controller_->FinishRecordProgressBar();
    watch_dog_->stop();
    QString path = NULL;
    QDir file_dir = QFileInfo(file_location_).absoluteDir();
    path = QFileDialog::getSaveFileName(
        canvas_, NULL, file_dir.filePath("name.gif"), "GIF (*.gif)", 0,
        QFileDialog::DontUseNativeDialog);
    if (!path.isNull()) gif_image_->save(path);
  }
}

/**
 * @brief Execute the GIF saving command.
 *
 * This method starts a timer that captures frames from the GlCanvas and adds
 * them to the GIF image until the specified number of frames is reached.
 */
void SaveGifCommand::execute() {
  watch_dog_ = new QTimer(this);
  item_controller_->StartRecordProgressBar();
  connect(watch_dog_, SIGNAL(timeout()), this, SLOT(AddFrameToGif_()));
  watch_dog_->start(100);
}

/**
 * @brief Destructor for the SaveGifCommand class.
 */
SaveGifCommand::~SaveGifCommand() {
  item_controller_->FinishRecordProgressBar();
  // Free dinamic allocated recources.
  delete gif_image_;
  delete watch_dog_;
}
}  // namespace s21
