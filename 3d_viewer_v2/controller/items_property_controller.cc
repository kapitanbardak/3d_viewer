#include "items_property_controller.h"

namespace s21 {
using std::string;
ItemsPropertyController::ItemsPropertyController(QMainWindow* window,
                                                 Ui_MainWindow* item_container,
                                                 GlCanvas* canvas)
    : main_window_(window), item_container_(item_container), canvas_(canvas) {
  SetButtonsNames_();
  SetItemsActivity(false);
  SetDefaultBoxValues_();
  SetDefaultTypesText_();

  ribs_pixmap_ = QPixmap(kPixmapSize_, kPixmapSize_);
  vertex_pixmap_ = QPixmap(kPixmapSize_, kPixmapSize_);
  background_pixmap_ = QPixmap(kPixmapSize_, kPixmapSize_);
  grids_pixmap_ = QPixmap(kPixmapSize_, kPixmapSize_);

  SetButtonIcons();
}

/**
 * @brief Iterates through all the buttons and boxes on the form, changing their
 * availability.
 * @param mode True - buttons are active, False - buttons are blocked.
 */
void ItemsPropertyController::SetItemsActivity(bool mode) {
  for (QDoubleSpinBox* box : main_window_->findChildren<QDoubleSpinBox*>())
    box->setEnabled(mode);

  for (QPushButton* button : main_window_->findChildren<QPushButton*>())
    if (!exclusions_.contains(button->objectName())) button->setEnabled(mode);

  for (auto p_bar : main_window_->findChildren<QProgressBar*>())
    if (!exclusions_.contains(p_bar->objectName())) p_bar->setVisible(false);
}

/**
 * @brief Sets the model information text on the UI.
 * @param path The path to the model.
 * @param name The name of the model.
 * @param vertex The count of vertices.
 * @param ribs The count of ribs.
 */
void ItemsPropertyController::SetModelInfoText(string path, string name,
                                               int vertex, int ribs) {
  std::stringstream ss;
  ss << "<html><head/><body><p align=\"center\">Model information</p>"
     << "<p>Name:"
     << "<span style=\" color:" << kColor_ << ";\">"
     << " " << name << "</span><br/>Count of vertices:"
     << "<span style=\" color:" << kColor_ << ";\">"
     << " " << vertex << "</span><br/>Count of ribs:"
     << "<span style=\" color:" << kColor_ << ";\">"
     << " " << ribs << "</span><br/>Path:"
     << "<span style=\" color:" << kColor_ << ";\">"
     << " " << path << "</span></p><p><br/></p></body></html>";

  std::string htmlText = ss.str();
  item_container_->model_info->setText(QString::fromStdString(htmlText));
}

/**
 * @brief Sets the text for vertex or ribs objects on the UI.
 *
 * @param text The text to set.
 * @param mode The mode (vertex or ribs).
 */
void ItemsPropertyController::SetObjectText(QString text, FunctionsMode mode) {
  if (mode == FunctionsMode::kVertex)
    item_container_->vertex_type_btn->setText(text);
  if (mode == FunctionsMode::kRibs)
    item_container_->ribs_type_btn->setText(text);
}

/**
 * @brief Sets the default values for box elements on the UI.
 */
void ItemsPropertyController::SetDefaultBoxValues_() {
  item_container_->vertex_size_box->setValue(canvas_->GetVertexSize());
  item_container_->ribs_size_box->setValue(canvas_->GetRibsWidth());
}

/**
 * @brief Sets the default text for types on the UI.
 */
void ItemsPropertyController::SetDefaultTypesText_() {
  item_container_->vertex_type_btn->setText(
      display_type_names_[static_cast<int>(canvas_->GetVertexType())]);
  item_container_->ribs_type_btn->setText(
      display_type_names_[static_cast<int>(canvas_->GetRibsType())]);
}

void ItemsPropertyController::SetProjectionButton() {
  ProjectionType saved_type = canvas_->GetProjectionType();

  item_container_->z_offset_box->setEnabled(saved_type ==
                                            ProjectionType::kCentral);
  item_container_->parallel_mode->setDown(saved_type ==
                                          ProjectionType::kParallel);
  item_container_->central_mode->setDown(saved_type ==
                                         ProjectionType::kCentral);
}

/**
 * @brief Sets the value of the X rotation box on the UI.
 *
 * @param value The value to set.
 */
void ItemsPropertyController::SetXRotationBoxValue(float value) {
  item_container_->x_rotation_box->setValue(value);
}

/**
 * @brief Sets the value of the Y rotation box on the UI.
 *
 * @param value The value to set.
 */
void ItemsPropertyController::SetYRotationBoxValue(float value) {
  item_container_->y_rotation_box->setValue(value);
}

void ItemsPropertyController::SetScaleBoxValue(float value) {
  item_container_->scale_spinbox->setValue(value);
}

float ItemsPropertyController::GetXRotationBoxValue() const {
  return item_container_->x_rotation_box->value();
}

float ItemsPropertyController::GetYRotationBoxValue() const {
  return item_container_->y_rotation_box->value();
}

float ItemsPropertyController::GetScaleBoxValue() const {
  return item_container_->scale_spinbox->value();
}

void ItemsPropertyController::SetButtonIcons() {
  background_pixmap_.fill(canvas_->GetItemColor(FunctionsMode::kBackground));
  ribs_pixmap_.fill(canvas_->GetItemColor(FunctionsMode::kRibs));
  vertex_pixmap_.fill(canvas_->GetItemColor(FunctionsMode::kVertex));
  grids_pixmap_.fill(canvas_->GetItemColor(FunctionsMode::kGrid));

  item_container_->background_color_btn->setIcon(QIcon(background_pixmap_));
  item_container_->grid_color_btn->setIcon(QIcon(grids_pixmap_));
  item_container_->ribs_color_btn->setIcon(QIcon(ribs_pixmap_));
  item_container_->vertex_color_btn->setIcon(QIcon(vertex_pixmap_));
}

QVector3D ItemsPropertyController::GetRotationValues() {
  return QVector3D(item_container_->x_rotation_box->value(),
                   item_container_->y_rotation_box->value(),
                   item_container_->z_rotation_box->value());
}

QVector3D ItemsPropertyController::GetMovementValues() {
  return QVector3D(item_container_->x_offset_box->value(),
                   item_container_->y_offset_box->value(),
                   item_container_->z_offset_box->value());
}

float ItemsPropertyController::GetSliderValue() const {
  return item_container_->sensitivity->value();
}

bool ItemsPropertyController::IsAllowedToChangeValues() {
  return item_container_->scale_spinbox->isEnabled();
}

QStringList& ItemsPropertyController::GetAllObjectNamesFromWindow() {
  return buttons_;
}

/**
 * @brief Retrieves the names of all buttons from the form and generates
 * a list of buttons that should remain active when the application starts.
 */
void ItemsPropertyController::SetButtonsNames_() {
  buttons_.append(item_container_->background_color_btn->objectName());
  buttons_.append(item_container_->ribs_color_btn->objectName());
  buttons_.append(item_container_->vertex_color_btn->objectName());
  buttons_.append(item_container_->load_object->objectName());
  buttons_.append(item_container_->set_def_position->objectName());
  buttons_.append(item_container_->save_to_pic->objectName());
  buttons_.append(item_container_->save_to_gif->objectName());
  buttons_.append(item_container_->vertex_size_box->objectName());
  buttons_.append(item_container_->ribs_size_box->objectName());
  buttons_.append(item_container_->vertex_type_btn->objectName());
  buttons_.append(item_container_->ribs_type_btn->objectName());
  buttons_.append(item_container_->parallel_mode->objectName());
  buttons_.append(item_container_->central_mode->objectName());
  buttons_.append(item_container_->grid_color_btn->objectName());

  exclusions_.append(buttons_.at(static_cast<int>(Names::kBackgroundColor)));
  exclusions_.append(buttons_.at(static_cast<int>(Names::kVertexColor)));
  exclusions_.append(buttons_.at(static_cast<int>(Names::kRibsColor)));
  exclusions_.append(buttons_.at(static_cast<int>(Names::kRibsType)));
  exclusions_.append(buttons_.at(static_cast<int>(Names::kVertexType)));
  exclusions_.append(buttons_.at(static_cast<int>(Names::kLoadObject)));
  exclusions_.append(buttons_.at(static_cast<int>(Names::kGridColor)));
}

void ItemsPropertyController::PlaceGlWindow() {
  item_container_->mainGrid->addWidget(canvas_, 0, 1, 6, 1);
}

void ItemsPropertyController::ResetBoxesValues() {
  for (QDoubleSpinBox* box : main_window_->findChildren<QDoubleSpinBox*>())
    box->setValue(0);
  item_container_->scale_spinbox->setValue(1);
}

/**
 * @brief Start record UI.
 */
void ItemsPropertyController::StartRecordProgressBar() {
  item_container_->progress_bar->setValue(0);
  item_container_->save_to_gif->setText("Recording...");
  item_container_->save_to_gif->setDisabled(true);
  item_container_->progress_bar->setVisible(true);
}

/**
 * @brief Set record UI progress.
 */
void ItemsPropertyController::SetRecordProgressBar(int value) {
  item_container_->progress_bar->setValue(value);
}

/**
 * @brief Finish record UI.
 */
void ItemsPropertyController::FinishRecordProgressBar() {
  item_container_->progress_bar->setVisible(false);
  item_container_->save_to_gif->setText("Save gif as...");
  item_container_->save_to_gif->setDisabled(false);
}
}  // namespace s21
