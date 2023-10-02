#include "open_file_command.h"

namespace s21 {
/**
 * @brief Constructor for the OpenFileCommand class.
 *
 * @brief Constructs an OpenFileCommand.
 * @param canvas A pointer to the GlCanvas.
 * @param object A pointer to the DataModel.
 * @param item_controller A pointer to the ItemsPropertyController.
 */
OpenFileCommand::OpenFileCommand(GlCanvas *canvas, DataModel *object,
                                 ItemsPropertyController *item_controller)
    : canvas_(canvas), object_(object), item_controller_(item_controller) {}

/**
 * @brief Execute the open file command.
 *
 * This method opens and loads a 3D model file, initializes the GlCanvas with
 * the model data, updates the GUI elements, and displays model information in
 * the main window.
 */
void OpenFileCommand::execute() {
  std::string path = QFileDialog::getOpenFileName().toStdString();
  if (!path.empty()) {
    object_->LoadModel(path);
    object_->Normalize();
    object_->ModelAlignmentCenter();
    object_->SetDefaultModelState();
    canvas_->InitializeArrays(object_->GetVertexArray(),
                              object_->GetIndicesArray());
    canvas_->SetArraysSize(object_->GetNumberOfVertexes(),
                           object_->GetNumberOfIndices());
    item_controller_->ResetBoxesValues();
    item_controller_->SetModelInfoText(
        object_->GetFilePath(), object_->GetFileName(),
        object_->GetNumberOfVertexes(), object_->GetNumberOfRibs());
    item_controller_->SetItemsActivity(true);
    item_controller_->SetProjectionButton();

    canvas_->repaint();
  }
}
}  // namespace s21
