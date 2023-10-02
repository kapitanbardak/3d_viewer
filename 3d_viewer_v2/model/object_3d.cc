#include "object_3d.h"

namespace s21 {
/**
 * @brief Constructor of the Object3D class.
 *
 * In the constructor, instances of strategies for applying object
 * transformations are created.
 */
Object3D::Object3D() {
  scale_strategy_ = new ScaleStrategy();
  move_strategy_ = new MoveStrategy();
  rotate_strategy_ = new RotateStrategy();
}

/**
 * @brief Get an instance of the Object3D class.
 *
 * This method creates and returns a static instance of the Object3D class,
 * which is used to manage the 3D object.
 *
 * @return Reference to an instance of the Object3D class.
 */
Object3D& Object3D::Instance() {
  static Object3D d;
  return d;
}

/**
 * @brief Get the vector of object points.
 *
 * @return Vector of object points.
 */
std::vector<float>& Object3D::Points() { return points_; }

/**
 * @brief Get the vector of object polygon indices.
 *
 * @return Vector of object polygon indices.
 */
std::vector<int>& Object3D::Indices() { return polygons_; }

/**
 * @brief Get the vector of object edges.
 *
 * @return Vector of object edges.
 */
std::vector<long int>& Object3D::Edges() { return edges_; }

/**
 * @brief Get the number of points in the object.
 *
 * @return Number of points.
 */
size_t Object3D::GetPointsAmount() { return points_.size(); }

/**
 * @brief Get the number of polygons in the object.
 *
 * @return Number of polygons.
 */
size_t Object3D::GetPolygonAmount() { return polygons_.size(); }

/**
 * @brief Get the number of unique edges in the object.
 *
 * @return Number of unique edges.
 */
size_t Object3D::GetEdgesAmount() {
  std::sort(edges_.begin(), edges_.end());
  return std::unique(edges_.begin(), edges_.end()) - edges_.begin();
}

/**
 * @brief
 * Considers the coordinates of a point, determining the minimum and maximum,
 * then writes the point to an array of points.
 * @param value The value of the new point.
 */
void Object3D::AddPoint(float value) {
  point_buffer_.push_back(value);
  if (point_buffer_.size() == 3) {
    if (point_buffer_ < minimum_point_values_)
      minimum_point_values_ = point_buffer_;
    else if (point_buffer_ > maximum_point_values_)
      maximum_point_values_ = point_buffer_;

    points_.insert(points_.end(), point_buffer_.begin(), point_buffer_.end());
    point_buffer_.clear();
  }
}

/**
 * @brief Add a new polygon index to the object.
 *
 * @param value The index of the new polygon.
 */
void Object3D::AddPolygonUnit(int value) { polygons_.push_back(value); }

/**
 * @brief Add a new edge to the object.
 *
 * @param value1 The first vertex of the edge.
 * @param value2 The second vertex of the edge.
 */
void Object3D::AddEdge(int value1, int value2) {
  if (value1 < value2) {
    int temp = value1;
    value1 = value2;
    value2 = temp;
  }
  long int result = 0;
  result = value1;
  result = result << sizeof(int);
  result += value2;
  edges_.push_back(result);
}

/**
 * @brief Apply scaling to the object.
 *
 * @param value Scaling factor.
 */
void Object3D::Scale(float value) { scale_strategy_->transform(value); }

/**
 * @brief Apply translation to the object.
 *
 * @param dx Translation along the X-axis.
 * @param dy Translation along the Y-axis.
 * @param dz Translation along the Z-axis.
 */
void Object3D::Move(float dx, float dy, float dz) {
  move_strategy_->transform({dx, dy, dz});
}

/**
 * @brief Apply rotation to the object.
 *
 * @param x Rotation angle around the X-axis.
 * @param y Rotation angle around the Y-axis.
 * @param z Rotation angle around the Z-axis.
 */
void Object3D::Rotate(float x, float y, float z) {
  rotate_strategy_->transform({x, y, z});
}

/**
 * @brief Set the path to the object.
 *
 * @param path Path to the object.
 */
void Object3D::SetPath(std::string path) { path_ = path; };

/**
 * @brief Get the path to the object.
 *
 * @return Path to the object.
 */
std::string Object3D::GetPath() { return path_; };

/**
 * @brief Reset the model to its default state.
 *
 * @param defaultPoints Vector of points to reset the model.
 */
void Object3D::ResetModelToDefaultState(std::vector<float>& defaultPoints) {
  points_ = defaultPoints;
}

/**
 * @brief Get maximum coordinates value in object points.
 * @return maximum point coordinate value.
 */
std::vector<float>& Object3D::GetMaximumPoint() {
  return maximum_point_values_;
}

/**
 * @brief Get minimum coordinates value in object points.
 * @return minimum point coordinate value.
 */
std::vector<float>& Object3D::GetMinimumPoint() {
  return minimum_point_values_;
}

/**
 * @brief Get a reference to the minimum point values of the object.
 */
std::vector<float>& Object3D::GetMinimumPointValues() {
  return minimum_point_values_;
}

/**
 * @brief Get a reference to the minimum point values of the object.
 */
std::vector<float>& Object3D::GetMaximumPointValues() {
  return maximum_point_values_;
}
}  // namespace s21
