#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  controller_ = new s21::Controller(ui_, this);
  ConnectButtonsAndSpinBoxes_();
}

MainWindow::~MainWindow() {
  delete ui_;
  delete controller_;
}

void MainWindow::ConnectButtonsAndSpinBoxes_() {
  for (QPushButton *button : findChildren<QPushButton *>())
    connect(button, &QPushButton::clicked, this, &MainWindow::ButtonClickSlot);
  for (QDoubleSpinBox *spinbox : findChildren<QDoubleSpinBox *>())
    connect(spinbox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
            &MainWindow::SpinBoxSlot);

  connect(ui_->sensitivity, &QSlider::sliderMoved, this,
          &MainWindow::SliderSlot);
}

void MainWindow::ButtonClickSlot() {
  QPushButton *clicked_button = qobject_cast<QPushButton *>(QObject::sender());
  try {
    controller_->ButtonHandler(clicked_button);
  } catch (const std::exception &ex) {
    std::string message = "The error occurred.\n";
    message += ex.what();
    QMessageBox::critical(this, tr("Error!"),
                          tr(const_cast<char *>(message.c_str())),
                          QMessageBox::Ok);
  }
}

void MainWindow::SpinBoxSlot() {
  QDoubleSpinBox *changed_spin_box =
      qobject_cast<QDoubleSpinBox *>(QObject::sender());
  controller_->BoxHandler(changed_spin_box);
}

void MainWindow::SliderSlot() { controller_->SliderHandler(); }

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
  controller_->MouseClickHandler(e);
}

void MainWindow::wheelEvent(QWheelEvent *e) {
  controller_->MouseWheelHandler(e);
}

void MainWindow::resizeEvent(QResizeEvent *e) {
  QImage image(":/images/background.png");
  if (!image.isNull()) {
    image =
        image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, QBrush(image));
    this->setPalette(p);
  }
}
