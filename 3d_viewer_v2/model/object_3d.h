#ifndef INC_3DVIEWER_V2_0_SRC_DATA_3D_H_
#define INC_3DVIEWER_V2_0_SRC_DATA_3D_H_

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "strategy/interface_object_transformation_strategy.h"
#include "strategy/move_strategy.h"
#include "strategy/rotate_strategy.h"
#include "strategy/scale_strategy.h"

namespace s21 {
/**
 * @brief The Object3D class represents a 3D object and provides methods for
 * manipulating it.
 */
class Object3D {
 public:
  /**
   * @brief Get a reference to the singleton instance of Object3D.
   * @return A reference to the Object3D instance.
   */
  static Object3D& Instance();

  /**
   * @brief Get the number of points in the object.
   * @return The number of points.
   */
  size_t GetPointsAmount();

  /**
   * @brief Get the number of polygons in the object.
   * @return The number of polygons.
   */
  size_t GetPolygonAmount();

  /**
   * @brief Get the number of edges in the object.
   * @return The number of edges.
   */
  size_t GetEdgesAmount();

  /**
   * @brief Get a reference to the points of the object.
   * @return A reference to the vector of points.
   */
  std::vector<float>& Points();

  /**
   * @brief Get a reference to the indices of the object.
   * @return A reference to the vector of indices.
   */
  std::vector<int>& Indices();

  /**
   * @brief Get a reference to the edges of the object.
   * @return A reference to the vector of edges.
   */
  std::vector<long int>& Edges();

  /**
   * @brief Reset the model to its default state using the provided default
   * points.
   * @param defaultPoints The default points to set the model to.
   */
  void ResetModelToDefaultState(std::vector<float>& defaultPoints);

  /**
   * @brief
   * Considers the coordinates of a point, determining the minimum and maximum,
   * then writes the point to an array of points.
   * @param value The value of the new point.
   */
  void AddPoint(float value);

  /**
   * @brief Add a polygon unit to the object.
   * @param value The value of the polygon unit to add.
   */
  void AddPolygonUnit(int value);

  /**
   * @brief Add an edge to the object.
   * @param value1 The first value of the edge.
   * @param value2 The second value of the edge.
   */
  void AddEdge(int value1, int value2);

  /**
   * @brief Set the file path of the object.
   * @param path The file path to set.
   */
  void SetPath(std::string path);

  /**
   * @brief Get the file path of the object.
   * @return The file path of the object.
   */
  std::string GetPath();

  /**
   * @brief Get a reference to the minimum point values of the object.
   * @return A reference to the vector of minimum points.
   */
  std::vector<float>& GetMinimumPointValues();

  /**
   * @brief Get a reference to the minimum point values of the object.
   * @return A reference to the vector of minimum points.
   */
  std::vector<float>& GetMaximumPointValues();

  /**
   * @brief Scale the object by a given value.
   * @param value The scale value.
   */
  void Scale(float value);

  /**
   * @brief Move the object by specified values in each dimension.
   * @param valueX The value to move the object in the X dimension.
   * @param valueY The value to move the object in the Y dimension.
   * @param valueZ The value to move the object in the Z dimension.
   */
  void Move(float valueX, float valueY, float valueZ);

  /**
   * @brief Rotate the object by specified values in each dimension.
   * @param valueX The value to rotate the object around the X axis.
   * @param valueY The value to rotate the object around the Y axis.
   * @param valueZ The value to rotate the object around the Z axis.
   */
  void Rotate(float valueX, float valueY, float valueZ);

  /**
   * @brief Get minimum coordinates value in object points.
   * @return minimum point coordinate value.
   */
  std::vector<float>& GetMinimumPoint();

  /**
   * @brief Get maximum coordinates value in object points.
   * @return maximum point coordinate value.
   */
  std::vector<float>& GetMaximumPoint();

  /**
   * @brief Casts all coordinate values ​​to the range -1 to 1.
   */
  void Normalize();

  /**
   * @brief Centers the model based on the minimum and maximum points.
   */
  void ModelAlignmentCenter();

 private:
  /**
   * @brief Constructor.
   */
  Object3D();

  /**
   * @brief Copy constructor (disabled).
   */
  Object3D(Object3D const&);

  /**
   * @brief Assignment operator (disabled).
   */
  Object3D& operator=(Object3D const&);

  std::string path_; /**< The file path of the object. */
  std::vector<float> minimum_point_values_ = {
      FLT_MAX, FLT_MAX, FLT_MAX}; /** < Minimum point coordinates. > */
  std::vector<float> maximum_point_values_ = {
      -FLT_MAX, -FLT_MAX, -FLT_MAX}; /** < Maximum point coordinates. > */
  std::vector<float> point_buffer_;  /** <Buffer for point coordinates. > */
  std::vector<float> points_;        /**< The vector of points in the object. */
  std::vector<float>
      default_points_; /**< The default points used for resetting the object. */
  std::vector<int>
      polygons_; /**< The vector of polygon indices in the object. */
  std::vector<long int>
      edges_; /**< The vector of edge indices in the object. */
  IObjectTransformationStrategy*
      scale_strategy_; /**< The strategy for scaling the object. */
  IObjectTransformationStrategy*
      move_strategy_; /**< The strategy for moving the object. */
  IObjectTransformationStrategy*
      rotate_strategy_; /**< The strategy for rotating the object. */
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_DATA_3D_H_
