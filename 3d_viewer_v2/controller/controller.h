#ifndef VIEWER_CONTROLLER_CONTROLLER_H
#define VIEWER_CONTROLLER_CONTROLLER_H

#include "commands/commands_list.h"
#include "core/glcanvas.h"
#include "cursorchecker.h"
#include "items_property_controller.h"
#include "model/interface/data_model.h"

namespace s21 {
/**
 * @brief Controller class responsible for handling user input and interactions.
 */
class Controller : QObject {
 public:
  /**
   * @brief Constructs a Controller object.
   * @param item_list A pointer to the main window UI.
   * @param main_window A pointer to the main window object.
   */
  Controller(Ui_MainWindow *item_list, QMainWindow *main_window);

  /**
   * @brief Destroys the Controller object.
   */
  ~Controller();

  /**
   * @brief Handles button click events.
   * @param button The clicked QPushButton.
   */
  void ButtonHandler(QPushButton *button);

  /**
   * @brief Handles changes in the QDoubleSpinBox controls.
   * @param box The QDoubleSpinBox that changed.
   */
  void BoxHandler(QDoubleSpinBox *box);

  /**
   * @brief Handles mouse move events.
   * @param event The mouse move event.
   */
  void MouseClickHandler(QMouseEvent *event);

  /**
   * @brief Handles mouse wheel events.
   * @param event The mouse wheel event.
   */
  void MouseWheelHandler(QWheelEvent *event);

  /**
   * @brief Handles slider move event.
   */
  void SliderHandler();

 private:
  GlCanvas *canvas_ = nullptr;  /**< Pointer to the GlCanvas. */
  DataModel *object_ = nullptr; /**< Pointer to the DataModel. */
  CursorChecker *cursor_checker_ =
      nullptr; /**< Pointer to the CursorChecker. */
  ItemsPropertyController *item_controller_ =
      nullptr; /**< Pointer to the ItemsPropertyController. */
  std::unique_ptr<ICommand>
      command_;         /**< Pointer to the current executing command. */
  QStringList buttons_; /** < A list of all buttons from the MainWindow > */
};
}  // namespace s21
#endif  // VIEWER_CONTROLLER_CONTROLLER_H
