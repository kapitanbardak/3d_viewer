#ifndef IDATAMODEL_H
#define IDATAMODEL_H

#include <string>
#include <vector>

#include "model/object_3d.h"
#include "model/parser.h"

namespace s21 {

/**
 * @brief The DataModel class represents the data model of the application.
 */
class DataModel {
 public:
  /**
   * @brief Constructs a DataModel object.
   */
  DataModel();

  /**
   * @brief Destructor for DataModel.
   */
  ~DataModel();

  /**
   * @brief Get the number of vertices in the model.
   * @return The number of vertices.
   */
  size_t GetNumberOfVertexes() const;

  /**
   * @brief Get the number of indices in the model.
   * @return The number of indices.
   */
  size_t GetNumberOfIndices() const;

  /**
   * @brief Get the number of ribs in the model.
   * @return The number of ribs.
   */
  size_t GetNumberOfRibs() const;

  /**
   * @brief Get a reference to the Object3D representing the model.
   * @return A reference to the Object3D.
   */
  Object3D &GetObjectModel() const;

  /**
   * @brief Load a 3D model from a file.
   * @param file_name The name of the 3D model file to load.
   */
  void LoadModel(const std::string &file_name);

  /**
   * @brief Reset the position of the model to its default state.
   */
  void ResetModelPosition();

  /**
   * @brief Move the position of the model.
   * @param dx The Ox vector of the movement.
   * @param dy The Oy vector of the movement.
   * @param dz The Oz vector of the movement.
   */
  void MoveModel(float dx, float dy, float dz);

  /**
   * @brief Rotate the position of the model.
   * @param dx The Ox angle of the rotation (degrees).
   * @param dy The Oy angle of the rotation (degrees).
   * @param dz The Oz angle of the rotation (degrees).
   */
  void RotateModel(float dx, float dy, float dz);

  /**
   * @brief Scale the size of the model.
   * @param scale_value The factor of the scaling.
   */
  void ScaleModel(float scale_value);

  /**
   * @brief Get the vertex array of the model.
   * @return A pointer to the vertex array.
   */
  float *GetVertexArray() const;

  /**
   * @brief Get the indices array of the model.
   * @return A pointer to the indices array.
   */
  int *GetIndicesArray() const;

  /**
   * @brief Get the filename of the loaded model.
   * @return The filename of the loaded model.
   */
  std::string GetFileName() const;

  /**
   * @brief Get the file path of the loaded model.
   * @return The file path of the loaded model.
   */
  std::string GetFilePath() const;

  /**
   * @brief Get the value of the coordinates of the farthest point.
   * @return value of the coordinates of the farthest point.
   */
  float *GetMaximumPoint() const;

  /**
   * @brief Get the value of the coordinates of the closest point.
   * @return value of the coordinates of the closest point.
   */
  float *GetMinimumPoint() const;

  /**
   * @brief Casts all coordinate values ​​to the range -1 to 1.
   */
  void Normalize();

  /**
   * @brief Centers the model based on the minimum and maximum points.
   */
  void ModelAlignmentCenter();

  /**
   * @brief Set default state of the model.
   */
  void SetDefaultModelState();

 private:
  Parser *parser_ =
      nullptr; /**< Pointer to the parser for reading 3D model files. */
  std::vector<float> default_model_state_; /**< Default state of the model. */
  float conversion_factor_ =
      3.14 / 180; /**< Final rotation conversion factor for converting from
                     radians to degrees. >*/
};

}  // namespace s21

#endif  // IDATAMODEL_H
