#ifndef VIEWER_CONTROLLER_COMMANDS_CHANGE_MODEL_COMMAND_H
#define VIEWER_CONTROLLER_COMMANDS_CHANGE_MODEL_COMMAND_H

#include "core/glcanvas.h"
#include "interface_controller_command.h"
#include "model/interface/data_model.h"

namespace s21 {
/**
 * @brief Command for changing the model's position or rotation in the GlCanvas.
 */
class ChangeModelCommand : public ICommand {
 public:
  /**
   * @brief Constructor for creating a command to change the model's position or
   * rotation.
   * @param canvas A pointer to the GlCanvas object.
   * @param rotation The coordinates for the change rotation angels.
   * @param movement The coordinates for the change translation.
   * @param scale The value for the change scale.
   */
  ChangeModelCommand(GlCanvas* canvas, const QVector3D& rotation,
                     const QVector3D& movement, float scale);

  /**
   * @brief Executes the command to change the model's position or rotation.
   */
  void execute() override;

 private:
  DataModel* object_ = nullptr; /**< A pointer to the DataModel object. */
  GlCanvas* canvas_ = nullptr;  /**< A pointer to the GlCanvas object. */
  QVector3D rotation_; /**< The coordinates for the change rotation angles. */
  QVector3D movement_; /**< The coordinates for the change translation. >*/
  float scale_ = 1;    /**< The value for the change scale. >*/
};
}  // namespace s21
#endif  // VIEWER_CONTROLLER_COMMANDS_CHANGE_MODEL_COMMAND_H
