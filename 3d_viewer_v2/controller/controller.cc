#include "controller.h"

namespace s21 {
/**
 * @brief Constructor for the Controller class.
 *
 * @param item_list Pointer to the application's compiled UI.
 * @param main_window Pointer to the application's main window.
 */
Controller::Controller(Ui_MainWindow *item_list, QMainWindow *main_window) {
  canvas_ = new GlCanvas();
  object_ = new DataModel();
  cursor_checker_ = new CursorChecker(canvas_);
  item_controller_ =
      new ItemsPropertyController(main_window, item_list, canvas_);
  item_controller_->PlaceGlWindow();
  buttons_ = item_controller_->GetAllObjectNamesFromWindow();
}

/**
 * @brief Handle button click events.
 * @param button Pointer to the clicked QPushButton.
 */
void Controller::ButtonHandler(QPushButton *button) {
  if (command_) command_.reset();
  QString button_object_name = button->objectName();
  if (button_object_name ==
      buttons_.at(static_cast<int>(Names::kBackgroundColor)))
    command_ =
        std::unique_ptr<ChangeItemColorCommand>(new ChangeItemColorCommand(
            canvas_, FunctionsMode::kBackground, item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kRibsColor)))
    command_ =
        std::unique_ptr<ChangeItemColorCommand>(new ChangeItemColorCommand(
            canvas_, FunctionsMode::kRibs, item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kVertexColor)))
    command_ =
        std::unique_ptr<ChangeItemColorCommand>(new ChangeItemColorCommand(
            canvas_, FunctionsMode::kVertex, item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kGridColor)))
    command_ =
        std::unique_ptr<ChangeItemColorCommand>(new ChangeItemColorCommand(
            canvas_, FunctionsMode::kGrid, item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kLoadObject)))
    command_ = std::unique_ptr<OpenFileCommand>(
        new OpenFileCommand(canvas_, object_, item_controller_));
  else if (button_object_name == buttons_.at(static_cast<int>(Names::kPicture)))
    command_ = std::unique_ptr<SaveImgCommand>(new SaveImgCommand(canvas_));
  else if (button_object_name == buttons_.at(static_cast<int>(Names::kGif)))
    command_ = std::unique_ptr<SaveGifCommand>(
        new SaveGifCommand(canvas_, item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kDefaultPosition)))
    command_ = std::unique_ptr<ResetPosition>(
        new ResetPosition(object_, canvas_, item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kVertexType)))
    command_ = std::unique_ptr<ChangeItemTypeCommand>(new ChangeItemTypeCommand(
        canvas_, item_controller_, FunctionsMode::kVertex));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kRibsType)))
    command_ = std::unique_ptr<ChangeItemTypeCommand>(new ChangeItemTypeCommand(
        canvas_, item_controller_, FunctionsMode::kRibs));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kParallelMode)))
    command_ = std::unique_ptr<ChangeProjectionModeCommand>(
        new ChangeProjectionModeCommand(canvas_, ProjectionType::kParallel,
                                        item_controller_));
  else if (button_object_name ==
           buttons_.at(static_cast<int>(Names::kCentralMode)))
    command_ = std::unique_ptr<ChangeProjectionModeCommand>(
        new ChangeProjectionModeCommand(canvas_, ProjectionType::kCentral,
                                        item_controller_));

  if (command_) command_->execute();
}

/**
 * @brief Handle changes in the input boxes.
 *
 * @param box Pointer to the changed QDoubleSpinBox.
 */
void Controller::BoxHandler(QDoubleSpinBox *box) {
  QString box_object_name = box->objectName();

  if (box_object_name == buttons_.at(static_cast<int>(Names::kVertexSize))) {
    ItemsSizeCommand(canvas_, FunctionsMode::kVertex, box->value()).execute();
  } else if (box_object_name ==
             buttons_.at(static_cast<int>(Names::kRibsSize))) {
    ItemsSizeCommand(canvas_, FunctionsMode::kRibs, box->value()).execute();
  } else {
    object_->ResetModelPosition();
    ChangeModelCommand(canvas_, item_controller_->GetRotationValues(),
                       item_controller_->GetMovementValues(),
                       item_controller_->GetScaleBoxValue())
        .execute();
  }
}

/**
 * @brief Handle mouse events.
 *
 * @param event Pointer to the QMouseEvent.
 */
void Controller::MouseClickHandler(QMouseEvent *event) {
  double x_current = event->pos().x(), y_current = event->pos().y();
  if (cursor_checker_->IsCanvasArea(x_current, y_current) &&
      item_controller_->IsAllowedToChangeValues()) {
    double x_box_value = item_controller_->GetXRotationBoxValue(),
           y_box_value = item_controller_->GetYRotationBoxValue();
    QVector4D coords(x_current, y_current, x_box_value, y_box_value);

    cursor_checker_->CalculateModelRotation(coords);
    item_controller_->SetXRotationBoxValue(cursor_checker_->x());
    item_controller_->SetYRotationBoxValue(cursor_checker_->y());
  }
}

void Controller::MouseWheelHandler(QWheelEvent *event) {
  float scale_step = 0.1f;
  if (item_controller_->IsAllowedToChangeValues()) {
    float value = item_controller_->GetScaleBoxValue();
    if (event->angleDelta().y() < 0)
      value -= scale_step;
    else
      value += scale_step;
    item_controller_->SetScaleBoxValue(value);
  }
}

void Controller::SliderHandler() {
  cursor_checker_->SetSensetivity(item_controller_->GetSliderValue());
}
/**
 * @brief Destructor for the Controller class.
 */
Controller::~Controller() {
  delete canvas_;
  delete object_;
}
}  // namespace s21
