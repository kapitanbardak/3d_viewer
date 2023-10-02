#include "change_model_command.h"

namespace s21 {
/**
 * @brief Constructor for the ChangeModelCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 * @param rotation The coordinates for the transformation.
 * @param rotation The movement for the transformation.
 */
ChangeModelCommand::ChangeModelCommand(GlCanvas* canvas,
                                       const QVector3D& rotation,
                                       const QVector3D& movement, float scale)
    : object_(new DataModel()),
      canvas_(canvas),
      rotation_(rotation),
      movement_(movement),
      scale_(scale) {}

/**
 * @brief Execute the model transformation command.
 *
 * This method applies a transformation to the DataModel object.
 * It then triggers a repaint of the canvas.
 */
void ChangeModelCommand::execute() {
  if (object_ != nullptr) {
    object_->ScaleModel(scale_);
    object_->RotateModel(rotation_.x(), rotation_.y(), rotation_.z());
    object_->MoveModel(movement_.x(), movement_.y(), movement_.z());
    canvas_->ChangePaintingArea(scale_);
    canvas_->repaint();
  }
}
}  // namespace s21
