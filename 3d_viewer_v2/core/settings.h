#ifndef VIEWER_CORE_SETTINGS_H
#define VIEWER_CORE_SETTINGS_H

#include <QColor>
#include <QSettings>
#include <QVariant>

#include "core/internal_names.h"

namespace s21 {
/**
 * @brief A class that stores settings for an OpenGl window.
 * Implements saving of some parameters between application sessions.
 * It also stores the default settings for the initial launch.
 */
class Settings {
 public:
  /**
   * @brief Constructor for Settings object.
   * @param settings
   */
  Settings(QSettings* settings);
  /**
   * @brief Returns the background color value.
   * @return QColor value.
   */
  QColor BackgroundColor() const;

  /**
   * @brief Sets the background color value.
   * @param color
   */
  void SetBackgroundColor(QColor color);

  /**
   * @brief Returns the vertex color value.
   * @return QColor value.
   */
  QColor VertexColor() const;

  /**
   * @brief Sets the vertex color value.
   * @param color
   */
  void SetVertexColor(QColor color);

  /**
   * @brief Returns the ribs color value.
   * @return QColor value.
   */
  QColor RibsColor() const;

  /**
   * @brief Sets the ribs color value.
   * @param color
   */
  void SetRibsColor(QColor color);

  /**
   * @brief Returns the vertex size value.
   * @return size float value.
   */
  float VertexSize() const;

  /**
   * @brief Sets the vertex size value.
   * @param size
   */
  void SetVertexSize(float size);

  /**
   * @brief Returns the ribs width value.
   * @return width float value.
   */
  float RibsWidth() const;

  /**
   * @brief Returns the ribs width value.
   * @param width
   */
  void SetRibsWidth(float width);

  /**
   * @brief Returns the vertex type value.
   * @return vertex type enum value.
   */
  enum VertexType VertexType() const;

  /**
   * @brief Returns the vertex type value.
   * @param type
   */
  void SetVertexType(enum VertexType type);

  /**
   * @brief Returns the ribs type value.
   * @return ribs type enum value.
   */
  enum RibsType RibsType() const;

  /**
   * @brief Sets the ribs type value.
   * @param type
   */
  void SetRibsType(enum RibsType type);

  /**
   * @brief Returns the projection type value.
   * @return projection type enum value.
   */
  enum ProjectionType ProjectionType() const;

  /**
   * @brief Sets the projection type value.
   * @param value
   */
  void SetProjectionType(enum ProjectionType value);

  /**
   * @brief Returns the grid color value.
   * @return QColor value.
   */
  QColor GridColor() const;

  /**
   * @brief Sets the grid color value.
   * @param color
   */
  void SetGridColor(QColor color);

 private:
  struct default_settings_ {
    float point_size = 1;
    float ribs_width = 1;
    QColor back_color = Qt::white;
    QColor point_color = Qt::red;
    QColor rib_color = Qt::black;
    QColor grid_color = Qt::black;
    int vertex_type = static_cast<int>(VertexType::kHard);
    int ribs_type = static_cast<int>(RibsType::kLine);
    int projection_mode = static_cast<int>(ProjectionType::kCentral);
  } default_settings_; /** < A structure that stores default settings. > */

  QSettings* settings_; /** < A pointer to QSettings object. > */
  QVariant background_color_;
  QVariant vertex_color_;
  QVariant ribs_color_;
  QVariant grid_color_;
  QVariant ribs_width_;
  QVariant vertex_size_;
  QVariant vertex_type_;
  QVariant ribs_type_;
  QVariant projection_type_;
};
}  // namespace s21
#endif  // VIEWER_CORE_SETTINGS_H
