#ifndef VIEWER_CORE_GLCANVAS_H
#define VIEWER_CORE_GLCANVAS_H

#include <QOpenGLWidget>
#include <QVector3D>
#include <QtOpenGL>

#include "settings.h"

#ifdef __APPLE__  // Для macOS
#include <GL/glut.h>
#else  // Для Linux и остальных платформ
#include <GL/glu.h>
#endif  // __APPLE__

namespace s21 {
/**
 * @brief The GlCanvas class describes the OpenGl window
 * in which the loaded model is drawn.
 */
class GlCanvas : public QOpenGLWidget {
 public:
  /**
   * @brief GlCanvas object constructor.
   * @param parent Pointer to parental object.
   */
  explicit GlCanvas(QOpenGLWidget* parent = nullptr);

  /**
   * @brief Sets projection type parameters.
   */
  void InitProjectionParameters(ProjectionType);

  /**
   * @brief Initializing vertex and index arrays.
   * @param vertexes Pointer to vertex array.
   * @param indicies Pointer to index array.
   */
  void InitializeArrays(float* vertexes, int* indicies);

  /**
   * @brief SetArraysSize sets the size of vertex and index arrays.
   * @param vertexSize Size of vertex array.
   * @param indiciesSize Size of index array.
   */
  void SetArraysSize(size_t vertexSize, size_t indiciesSize);

  /**
   * @brief Sets color of ribs/vertex/background/grid based on mode.
   * @param color
   * @param mode
   */
  void SetColor(QColor color, FunctionsMode mode);

  /**
   * @brief Returns the color value of edges/vertices/background/grid based on
   * mode.
   * @param mode
   * @return QColor value.
   */
  QColor GetItemColor(FunctionsMode mode);

  /**
   * @brief Sets the size of vertices.
   * @param size
   */
  void SetVertexSize(float size);

  /**
   * @brief Returns the size of vertices.
   * @return size float value.
   */
  float GetVertexSize() const;

  /**
   * @brief Sets the width of ribs.
   * @param width
   */
  void SetRibsWidth(float width);

  /**
   * @brief Returns the width of ribs.
   * @return width float value.
   */
  float GetRibsWidth() const;

  /**
   * @brief Sets the type of vertices (hard/smooth/none) based on type enum
   * value.
   * @param type
   */
  void SetVertexType(VertexType type);

  /**
   * @brief Returns the current type of vertices.
   * @return vertex type enum value.
   */
  VertexType GetVertexType() const;

  /**
   * @brief Sets the type of ribs (line/dotted) based on type enum value.
   * @param type
   */
  void SetRibsType(RibsType type);

  /**
   * @brief Returns the current type of ribs.
   * @return ribs type enum value.
   */
  RibsType GetRibsType() const;

  /**
   * @brief Returns the current projection type.
   * @return projection type enum value.
   */
  ProjectionType GetProjectionType() const;

  /**
   * @brief Sets the type of the projection (central/ parralel) based on current
   * type.
   */
  void SetProjectionType();

  /**
   * @brief Sets the edges of the rendering field depending on the scale of the
   * model.
   * @param scale Model scale value.
   */
  void ChangePaintingArea(const float scale);

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

 private:
  /**
   * @brief Set camera direction and position.
   * @param mode Type of  projection.
   */
  void SetCamera_(ProjectionType mode);

  /**
   * @brief Draws a grid on the field according to the coordinates specified in
   * grid_.
   * @see Grid structure.
   */
  void DrawGrid_();

  /**
   * @brief Draws model vertices on the field according to the coordinates
   * specified in vertex_array_.
   */
  void DrawVertices_();

  /**
   * @brief Draws model ribs on the field according to the coordinates specified
   * in indicies_array_.
   */
  void DrawRibs_();

  QSettings* settings_ = nullptr;     /** < Pointer to QSettings object. > */
  Settings* settings_list_ = nullptr; /** < Pointer to Settings object which
                                         contains settings for app. > */

  float* vertices_array_ = nullptr; /** < Pointer to vertex array. > */
  int* indicies_array_ = nullptr;   /** < Pointer to index array. > */
  size_t number_of_vertexes_ = 0;   /** < Number of vertexes. > */
  size_t number_of_indicies_ = 0;   /** < Number of indicies.> */

  GLfloat ratio_ = 1.0f;  /** < GlWindow aspect ratio > */
  GLfloat width_ = 0.0f;  /** < GlWindow width > */
  GLfloat height_ = 0.0f; /** < GlWindow height > */

  QVector<float> camera_position_ = {
      0, 0, 3, 0, 0,
      0, 0, 1, 0}; /** < A vector containing camera coordinate values (angle,
                      look direction). > */

  struct Frustum {
    float edge = 1;
    float far_edge = 20;
    float left = -edge;
    float right = edge;
    float up = edge;
    float down = -edge;
    float near_value = 1;
    float far_value = far_edge;
  } Frustum_; /** < A structure containing parameters for the size of the drawn
                 volume for Frustum projection > */

  struct Ortho {
    float edge = 2;
    float far_edge = 20;
    float left = -edge;
    float right = edge;
    float up = edge;
    float down = -edge;
    float near_value = 1;
    float far_value = far_edge;
  } Ortho_; /** < A structure containing parameters for the size of the drawn
               volume for Ortho projection > */

  /**
   * @brief The Grid struct
   * A structure that stores coordinates for drawing a grid in a window.
   * All coordinates are hardcoded and do not change during program operation.
   */
  struct Grid {
    static const size_t kNumberOfIndicies = 20;
    float grid_coordinates[16][3] = {
        {-4, -1, 4},   {4, -1, 4},   {4, -1, -2},    {-4, -1, -2}, {-2, -1, 4},
        {-2, -1, -2},  {0, -1, 4},   {0, -1, -2},    {2, -1, 4},   {2, -1, -2},
        {-4, -1, 1.5}, {4, -1, 1.5}, {-4, -1, -0.5}, {4, -1, -0.5}};
    unsigned int grid_indicies[kNumberOfIndicies] = {
        0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  } grid_; /** < A structure that stores coordinates for drawing a grid in a
            * window. All coordinates are hardcoded and do not change during
            * program operation. > */
};
}  // namespace s21
#endif  // VIEWER_CORE_GLCANVAS_H
