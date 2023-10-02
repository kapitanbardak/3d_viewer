#include "change_item_type_command.h"

namespace s21 {
/**
 * @brief Constructor for the ChangeItemTypeCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 * @param mode The mode in which to change the item type.
 */
ChangeItemTypeCommand::ChangeItemTypeCommand(
    GlCanvas* canvas, ItemsPropertyController* controller, FunctionsMode mode)
    : canvas_(canvas), item_controller_(controller), mode_(mode) {}

/**
 * @brief Execute the item type change command.
 *
 * This method changes the type of items (vertex or ribs) in the GlCanvas object
 * and triggers a repaint.
 */
void ChangeItemTypeCommand::execute() {
  if (mode_ == FunctionsMode::kVertex) {
    switch (canvas_->GetVertexType()) {
      case VertexType::kHard:
        canvas_->SetVertexType(VertexType::kSmooth);
        item_controller_->SetObjectText("Smooth", mode_);
        break;
      case VertexType::kSmooth:
        canvas_->SetVertexType(VertexType::kTransparent);
        item_controller_->SetObjectText("None", mode_);
        break;
      case VertexType::kTransparent:
        canvas_->SetVertexType(VertexType::kHard);
        item_controller_->SetObjectText("Hard", mode_);
        break;
      default:
        break;
    }
  }
  if (mode_ == FunctionsMode::kRibs) {
    switch (canvas_->GetRibsType()) {
      case RibsType::kLine:
        canvas_->SetRibsType(RibsType::kDotted);
        item_controller_->SetObjectText("Dotted", mode_);
        break;
      case RibsType::kDotted:
        canvas_->SetRibsType(RibsType::kLine);
        item_controller_->SetObjectText("Line", mode_);
        break;
      default:
        break;
    }
  }
  canvas_->repaint();
}
}  // namespace s21
