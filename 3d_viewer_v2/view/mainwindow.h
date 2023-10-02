#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleSpinBox>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class represents the main application window.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructor for the MainWindow class.
   * @param parent The parent widget, if any.
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor for the MainWindow class.
   */
  ~MainWindow();

 protected:
  /**
   * @brief Override of the mouse move event handler.
   * @param e The mouse event.
   */
  void mouseMoveEvent(QMouseEvent *e) override;

  /**
   * @brief Override of the wheel move event handler.
   * @param e The wheel event.
   */
  void wheelEvent(QWheelEvent *e) override;

  /**
   * @brief Override of the resize event handler.
   * @param e The resize event.
   */
  void resizeEvent(QResizeEvent *e) override;

 private:
  /**
   * @brief Connects buttons and spin boxes to their respective slots.
   */
  void ConnectButtonsAndSpinBoxes_();

  Ui::MainWindow *ui_; /**< The user interface object. */
  s21::Controller *
      controller_; /**< The controller object for handling user interactions. */

 private slots:
  /**
   * @brief Slot to handle button clicks.
   */
  void ButtonClickSlot();

  /**
   * @brief Slot to handle changes in spin box values.
   */
  void SpinBoxSlot();

  void SliderSlot();
};
#endif  // MAINWINDOW_H
