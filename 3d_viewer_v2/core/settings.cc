#include "settings.h"

namespace s21 {
Settings::Settings(QSettings* settings) : settings_(settings) {
  background_color_ =
      settings->value("backgroundColor",
                      background_color_ = QColor(default_settings_.back_color));
  vertex_color_ = settings_->value(
      "vertexColor", vertex_color_ = QColor(default_settings_.point_color));
  ribs_color_ = settings_->value(
      "ribsColor", ribs_color_ = QColor(default_settings_.rib_color));
  grid_color_ = settings_->value(
      "gridColor", grid_color_ = QColor(default_settings_.grid_color));
  vertex_size_ = settings_->value("vertexSize",
                                  vertex_size_ = default_settings_.point_size);
  ribs_width_ =
      settings_->value("ribsWidth", ribs_width_ = default_settings_.ribs_width);
  vertex_type_ = settings_->value(
      "vertexType", vertex_type_ = (default_settings_.vertex_type));
  ribs_type_ =
      settings_->value("ribsType", ribs_type_ = (default_settings_.ribs_type));
  projection_type_ =
      settings_->value("projection_type_",
                       projection_type_ = (default_settings_.projection_mode));
}

QColor Settings::BackgroundColor() const {
  return background_color_.value<QColor>();
}

void Settings::SetBackgroundColor(QColor color) {
  settings_->setValue("backgroundColor", background_color_ = color);
}

QColor Settings::VertexColor() const { return vertex_color_.value<QColor>(); }

void Settings::SetVertexColor(QColor color) {
  settings_->setValue("vertexColor", vertex_color_ = color);
}

QColor Settings::RibsColor() const { return ribs_color_.value<QColor>(); }

void Settings::SetRibsColor(QColor color) {
  settings_->setValue("ribsColor", ribs_color_ = color);
}

float Settings::VertexSize() const { return vertex_size_.value<float>(); }

void Settings::SetVertexSize(float size) {
  settings_->setValue("vertexSize", vertex_size_ = size);
}

float Settings::RibsWidth() const { return ribs_width_.value<float>(); }

void Settings::SetRibsWidth(float width) {
  settings_->setValue("ribsWidth", ribs_width_ = width);
}

VertexType Settings::VertexType() const {
  return static_cast<enum VertexType>(vertex_type_.value<int>());
}

void Settings::SetVertexType(enum VertexType type) {
  settings_->setValue("vertexType", vertex_type_ = static_cast<int>(type));
}

RibsType Settings::RibsType() const {
  return static_cast<enum RibsType>(ribs_type_.value<int>());
}

void Settings::SetRibsType(enum RibsType type) {
  settings_->setValue("ribsType", ribs_type_ = static_cast<int>(type));
}

ProjectionType Settings::ProjectionType() const {
  return static_cast<enum ProjectionType>(projection_type_.value<int>());
}

void Settings::SetProjectionType(enum ProjectionType value) {
  settings_->setValue("projection_type_",
                      projection_type_ = static_cast<int>(value));
}

QColor Settings::GridColor() const { return grid_color_.value<QColor>(); }

void Settings::SetGridColor(QColor color) {
  settings_->setValue("gridColor", grid_color_ = color);
}
}  // namespace s21
