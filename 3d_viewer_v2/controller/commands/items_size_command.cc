#include "items_size_command.h"

namespace s21 {
/**
 * @brief Constructor for the ItemsSizeCommand class.
 *
 * @param canvas Pointer to the GlCanvas object.
 * @param mode The mode in which to change item size (vertex or ribs).
 * @param size The new size to be applied.
 */
ItemsSizeCommand::ItemsSizeCommand(GlCanvas* canvas, FunctionsMode mode,
                                   float size)
    : canvas_(canvas), mode_(mode), size_(size) {}

/**
 * @brief Execute the item size change command.
 *
 * This method changes the size of items (vertex or ribs) in the GlCanvas object
 * based on the specified mode and the provided size. It then triggers a
 * repaint.
 */
void ItemsSizeCommand::execute() {
  if (mode_ == FunctionsMode::kVertex) canvas_->SetVertexSize(size_);
  if (mode_ == FunctionsMode::kRibs) canvas_->SetRibsWidth(size_);
  canvas_->repaint();
}
}  // namespace s21
