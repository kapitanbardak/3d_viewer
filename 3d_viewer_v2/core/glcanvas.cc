#include "glcanvas.h"

namespace s21 {
GlCanvas::GlCanvas(QOpenGLWidget* parent) : QOpenGLWidget{parent} {
  settings_ = new QSettings("./settings.ini", QSettings::IniFormat);
  settings_list_ = new Settings(settings_);
  setMinimumSize(600, 600);
}

void GlCanvas::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * @brief Calculates the aspect ratio when resizing the window in order
 * to subsequently maintain the proportions of the rendering windo
 */
void GlCanvas::resizeGL(int nWidth, int nHeight) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  width_ = nWidth;
  height_ = nHeight;
  ratio_ = (GLfloat)nHeight / (GLfloat)nWidth;
  glViewport(0, 0, width_, height_);
}

/**
 * @brief Draws vertices and edges based on the passed arrays of vertices and
 * indices.
 */
void GlCanvas::paintGL() {
  QColor b_color = settings_list_->BackgroundColor();

  glClearColor(b_color.redF(), b_color.greenF(), b_color.blueF(),
               b_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SetProjectionType();

  DrawGrid_();
  DrawVertices_();
  DrawRibs_();
}

void GlCanvas::DrawGrid_() {
  if (settings_list_->ProjectionType() == ProjectionType::kCentral) {
    QColor g_color = settings_list_->GridColor();

    glVertexPointer(3, GL_FLOAT, 0, grid_.grid_coordinates);
    glColor3d(g_color.redF(), g_color.greenF(), g_color.blueF());
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, grid_.kNumberOfIndicies, GL_UNSIGNED_INT,
                   grid_.grid_indicies);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void GlCanvas::DrawVertices_() {
  if (vertices_array_) {
    QColor v_color = settings_list_->VertexColor();
    VertexType v_type = settings_list_->VertexType();

    glVertexPointer(3, GL_FLOAT, 0, vertices_array_);
    glPointSize(settings_list_->VertexSize());
    glColor3d(v_color.redF(), v_color.greenF(), v_color.blueF());
    glEnableClientState(GL_VERTEX_ARRAY);
    if (v_type == VertexType::kSmooth) glEnable(GL_POINT_SMOOTH);
    if (v_type != VertexType::kTransparent)
      glDrawArrays(GL_POINTS, 0, number_of_vertexes_);
    if (v_type == VertexType::kSmooth) glDisable(GL_POINT_SMOOTH);
  }
}

void GlCanvas::DrawRibs_() {
  if (indicies_array_) {
    QColor r_color = settings_list_->RibsColor();
    RibsType r_type = settings_list_->RibsType();

    glColor3d(r_color.redF(), r_color.greenF(), r_color.blueF());
    glLineStipple(1, 0x00FF);
    if (r_type == RibsType::kDotted) glEnable(GL_LINE_STIPPLE);
    glLineWidth(settings_list_->RibsWidth());
    glDrawElements(GL_LINES, number_of_indicies_, GL_UNSIGNED_INT,
                   indicies_array_);
    if (r_type == RibsType::kDotted) glDisable(GL_LINE_STIPPLE);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void GlCanvas::InitProjectionParameters(ProjectionType value) {
  settings_list_->SetProjectionType(value);
  SetProjectionType();
}

/**
 * @note The default parameter in switch explicitly specifies to skip the
 * remaining types in the enumeration.
 */
void GlCanvas::SetColor(QColor color, FunctionsMode mode) {
  switch (mode) {
    case FunctionsMode::kBackground:
      settings_list_->SetBackgroundColor(color);
      break;
    case FunctionsMode::kRibs:
      settings_list_->SetRibsColor(color);
      break;
    case FunctionsMode::kVertex:
      settings_list_->SetVertexColor(color);
      break;
    case FunctionsMode::kGrid:
      settings_list_->SetGridColor(color);
      break;
    default:
      break;
  }
}

QColor GlCanvas::GetItemColor(FunctionsMode mode) {
  switch (mode) {
    case FunctionsMode::kBackground:
      return settings_list_->BackgroundColor();
    case FunctionsMode::kRibs:
      return settings_list_->RibsColor();
    case FunctionsMode::kVertex:
      return settings_list_->VertexColor();
    case FunctionsMode::kGrid:
      return settings_list_->GridColor();
    default:
      return QColor::Invalid;
  }
}

void GlCanvas::SetVertexSize(float size) {
  settings_list_->SetVertexSize(size);
}

float GlCanvas::GetVertexSize() const { return settings_list_->VertexSize(); }

void GlCanvas::SetRibsWidth(float width) {
  settings_list_->SetRibsWidth(width);
}

float GlCanvas::GetRibsWidth() const { return settings_list_->RibsWidth(); }

void GlCanvas::SetVertexType(VertexType type) {
  settings_list_->SetVertexType(type);
}

VertexType GlCanvas::GetVertexType() const {
  return settings_list_->VertexType();
}

void GlCanvas::SetRibsType(RibsType type) { settings_list_->SetRibsType(type); }

RibsType GlCanvas::GetRibsType() const { return settings_list_->RibsType(); }

ProjectionType GlCanvas::GetProjectionType() const {
  return settings_list_->ProjectionType();
}

void GlCanvas::InitializeArrays(float* vertexes, int* indicies) {
  vertices_array_ = vertexes;
  indicies_array_ = indicies;
}

void GlCanvas::SetArraysSize(size_t vertexSize, size_t indiciesSize) {
  number_of_indicies_ = indiciesSize;
  number_of_vertexes_ = vertexSize;
}

/**
 * If the scale is less than one, then the border remains default.
 * Otherwise it is multiplied by the scale.
 */
void GlCanvas::ChangePaintingArea(const float scale) {
  if (scale > 1)
    Frustum_.far_value = Frustum_.far_edge * scale;
  else
    Frustum_.far_value = Frustum_.far_edge;

  Ortho_.far_value = Frustum_.far_value;
}

/**
 * @brief Set the projection type for the OpenGL canvas.
 *
 * This function sets the projection type of the OpenGL canvas based on the
 * current settings. If the projection type is set to CENTRAL, it uses a
 * perspective projection (glFrustum). Otherwise, it uses an orthographic
 * projection (glOrtho).
 * @see ProjectionType
 */
void GlCanvas::SetProjectionType() {
  ProjectionType current_projection = settings_list_->ProjectionType();
  switch (current_projection) {
    case ProjectionType::kCentral:  // Normal Graphics
      if (width_ >= height_) {
        glFrustum(Frustum_.left / ratio_, Frustum_.right / ratio_,
                  Frustum_.down, Frustum_.up, Frustum_.near_value,
                  Frustum_.far_value);
      } else {
        glFrustum(Frustum_.left, Frustum_.right, Frustum_.down * ratio_,
                  Frustum_.up * ratio_, Frustum_.near_value,
                  Frustum_.far_value);
      }
      break;
    case ProjectionType::kParallel:  // Orthographic Graphics
      if (width_ >= height_) {
        glOrtho(Ortho_.left / ratio_, Ortho_.right / ratio_, Ortho_.down,
                Ortho_.up, Ortho_.near_value, Ortho_.far_value);
      } else {
        glOrtho(Ortho_.left, Ortho_.right, Ortho_.down * ratio_,
                Ortho_.up * ratio_, Ortho_.near_value, Ortho_.far_value);
      }
      break;
  }
  glTranslatef(0, 0, -camera_position_[2]);
  SetCamera_(current_projection);
}

/**
 * @brief Depending on the type of projection, sets the position and direction
 * of the camera.
 */
void GlCanvas::SetCamera_(ProjectionType mode) {
  switch (mode) {
    case ProjectionType::kCentral:
      camera_position_[0] = -1;
      camera_position_[1] = 1;
      break;
    case ProjectionType::kParallel:
      camera_position_[0] = 0;
      camera_position_[1] = 0;
  }
  gluLookAt(camera_position_[0], camera_position_[1], camera_position_[2],
            camera_position_[3], camera_position_[4], camera_position_[5],
            camera_position_[6], camera_position_[7], camera_position_[8]);
}
}  // namespace s21
