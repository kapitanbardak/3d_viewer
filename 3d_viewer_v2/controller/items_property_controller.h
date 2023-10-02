#ifndef VIEWER_COMMANDS_ITEMSPROPERTYCONTROLLER_H
#define VIEWER_COMMANDS_ITEMSPROPERTYCONTROLLER_H

#include <map>
#include <sstream>

#include "core/glcanvas.h"
#include "ui_mainwindow.h"

namespace s21 {
using std::string;
using std::stringstream;
/**
 * @brief The ItemsPropertyController class is responsible for managing the
 * properties of the form objects.
 */
class ItemsPropertyController {
 public:
  /**
   * @brief Constructs ItemsPropertyController object.
   * @param window A pointer to the main window object.
   * @param item_container A pointer to the main window UI.
   * @param canvas A pointer to the GlCanvas object.
   */
  ItemsPropertyController(QMainWindow* window, Ui_MainWindow* item_container,
                          GlCanvas* canvas);

  /**
   * @brief Sets the eneabled value of buttons and spinboxes to mode, ignoring
   * buttons from the exclusion list.
   * @param mode Value ​​for the enabled flag.
   */
  void SetItemsActivity(bool mode);

  /**
   * @brief Sets the text to the model information label.
   * @param path Model path.
   * @param name Model name.
   * @param vertex Number of vertices.
   * @param ribs Number of ribs.
   */
  void SetModelInfoText(string path, string name, int vertex, int ribs);

  /**
   * @brief Sets the text to the object.
   * @param text
   * @param mode
   */
  void SetObjectText(QString text, FunctionsMode mode);

  /**
   * @brief Sets the pressed and unpressed states for projections buttons
   * deffined by the settings.
   */
  void SetProjectionButton();

  /**
   * @brief Sets the color iconst for colorizing buttons defined by the
   * settings.
   */
  void SetButtonIcons();

  /**
   * @brief Sets the value of x rotation spinbox.
   * @param value rotation.
   */
  void SetXRotationBoxValue(float value);

  /**
   * @brief Sets the value of y rotation spinbox.
   * @param value rotation.
   */
  void SetYRotationBoxValue(float value);

  /**
   * @brief Sets the value of scale spinbox.
   * @param value scale.
   */
  void SetScaleBoxValue(float value);

  /**
   * @brief Gets the value of x rotation spinbox.
   * @param value rotation.
   */
  float GetXRotationBoxValue() const;

  /**
   * @brief Gets the value of y rotation spinbox.
   * @param value rotation.
   */
  float GetYRotationBoxValue() const;

  /**
   * @brief Gets the value of scale spinbox.
   * @param value scale.
   */
  float GetScaleBoxValue() const;

  /**
   * @brief Gets rotation values ​​on all three axes.
   * @return QVector3D object which contains rotation values.
   */
  QVector3D GetRotationValues();

  /**
   * @brief Gets movement values ​​on all three axes.
   * @return QVector3D object which contains movement values.
   */
  QVector3D GetMovementValues();

  /**
   * @brief Gets value of sensitivity slider.
   * @return value of sensitivity
   */
  float GetSliderValue() const;

  /**
   * @brief Indicates whether changing the values ​​in the boxes is allowed.
   * @return
   */
  bool IsAllowedToChangeValues();

  /**
   * @brief Gets a list of buttons placed on the form.
   * @return
   */
  QStringList& GetAllObjectNamesFromWindow();

  /**
   * @brief Places a window on an Opengl form.
   */
  void PlaceGlWindow();

  /**
   * @brief Resets the box values ​​to 0.
   */
  void ResetBoxesValues();

  /**
   * @brief Start record UI.
   */
  void StartRecordProgressBar();

  /**
   * @brief Set record UI progress.
   */
  void SetRecordProgressBar(int value);

  /**
   * @brief Finish record UI.
   */
  void FinishRecordProgressBar();

 private:
  /**
   * @brief Sets the default value of the text on the buttons, based on the
   * settings.
   */
  void SetDefaultTypesText_();

  /**
   * @brief Sets the default value of the text on the spinboxes, based on the
   * settings.
   */
  void SetDefaultBoxValues_();

  /**
   * @brief Collects a list of buttons from the form and generates a list of
   * names of active buttons.
   */
  void SetButtonsNames_();

  QMainWindow* main_window_ =
      nullptr; /** <A pointer to the main window object> */
  Ui_MainWindow* item_container_ =
      nullptr;                 /** <A pointer to the main window UI.>*/
  GlCanvas* canvas_ = nullptr; /** <A pointer to the GlCanvas object.> */
  QStringList exclusions_;     /** < A list of buttons that should remain active
                                  when the application starts. > */
  QStringList buttons_; /** < A list of all buttons from the MainWindow > */

  std::map<int, QString> display_type_names_{
      {static_cast<int>(VertexType::kTransparent),
       "None"}, /** <Mapping of vertex types to display names.> */
      {static_cast<int>(VertexType::kHard), "Hard"},
      {static_cast<int>(VertexType::kSmooth), "Smooth"},
      {static_cast<int>(RibsType::kDotted),
       "Dotted"}, /** <Mapping of ribs types to display names.> */
      {static_cast<int>(RibsType::kLine), "Line"}};

  QPixmap ribs_pixmap_;       /** <Pixmap for ribs.> */
  QPixmap vertex_pixmap_;     /** <Pixmap for vertices.> */
  QPixmap background_pixmap_; /** <Pixmap for the background color.> */
  QPixmap grids_pixmap_;      /** <Pixmap for grids.> */

  const int kPixmapSize_ = 5;            /** <Size of the pixmaps.> */
  const std::string kColor_ = "#222b36"; /** <Default color code.> */
};
}  // namespace s21

#endif  // VIEWER_COMMANDS_ITEMSPROPERTYCONTROLLER_H
