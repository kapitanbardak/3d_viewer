#include "data_model.h"

#include "model/object_3d.h"

namespace s21 {
/**
 * @brief Constructor for the DataModel class.
 */
DataModel::DataModel() : parser_(new Parser()) {}

/**
 * @brief Get the file name from the loaded model's path.
 *
 * @return The file name of the loaded model.
 */
std::string DataModel::GetFileName() const {
  std::string path = Object3D::Instance().GetPath();
  std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
  return base_filename;
}

/**
 * @brief Get the file path from the loaded model's path.
 *
 * @return The file path of the loaded model.
 */
std::string DataModel::GetFilePath() const {
  std::string full_path = Object3D::Instance().GetPath();
  std::string::size_type const p(full_path.find_last_of("/\\"));
  std::string file_path = full_path.substr(0, p);
  return file_path;
}

/**
 * @brief Load a 3D model from a file.
 *
 * @param file_name The path to the 3D model file.
 */
void DataModel::LoadModel(const std::string &file_name) {
  if (parser_) parser_->ReadObject(file_name);
}

/**
 * @brief Casts all coordinate values ​​to the range -1 to 1.
 */
void DataModel::Normalize() {
  float length = 0;

  for (size_t i = 0; i < Object3D::Instance().GetMaximumPointValues().size();
       i++) {
    float n = Object3D::Instance().GetMaximumPointValues()[i] *
              Object3D::Instance().GetMaximumPointValues()[i];
    length += n;
  }

  length = sqrtf(length);

  for (size_t i = 0; i < Object3D::Instance().Points().size(); ++i)
    Object3D::Instance().Points()[i] /= length;

  for (size_t i = 0; i < Object3D::Instance().GetMaximumPointValues().size();
       ++i) {
    Object3D::Instance().GetMaximumPointValues()[i] /= length;
    Object3D::Instance().GetMinimumPointValues()[i] /= length;
  }
}

/**
 * @brief Centers the model based on the minimum and maximum points.
 */
void DataModel::ModelAlignmentCenter() {
  std::vector<float> coordinates_delta{0, 0, 0};
  for (size_t i = 0; i < coordinates_delta.size(); ++i)
    coordinates_delta[i] = -(Object3D::Instance().GetMaximumPointValues()[i] +
                             Object3D::Instance().GetMinimumPointValues()[i]) /
                           2;
  Object3D::Instance().Move(coordinates_delta[0], coordinates_delta[1],
                            coordinates_delta[2]);
}

/**
 * @brief Set default state of the model.
 */
void DataModel::SetDefaultModelState() {
  default_model_state_ = GetObjectModel().Points();
}

/**
 * @brief Get the number of vertices in the loaded model.
 *
 * @return The number of vertices.
 */
size_t DataModel::GetNumberOfVertexes() const {
  return Object3D::Instance().GetPointsAmount() / 3;
}

/**
 * @brief Get the number of indices (polygons) in the loaded model.
 *
 * @return The number of indices (polygons).
 */
size_t DataModel::GetNumberOfIndices() const {
  return Object3D::Instance().GetPolygonAmount();
}

/**
 * @brief Get the number of unique edges in the loaded model.
 *
 * @return The number of unique edges.
 */
size_t DataModel::GetNumberOfRibs() const {
  return Object3D::Instance().GetEdgesAmount();
}

/**
 * @brief Reset the model's position to its default state.
 */
void DataModel::ResetModelPosition() {
  GetObjectModel().ResetModelToDefaultState(default_model_state_);
}

/**
 * @brief Get the vertex array of the loaded model.
 *
 * @return A pointer to the vertex array.
 */
float *DataModel::GetVertexArray() const {
  return Object3D::Instance().Points().data();
}

/**
 * @brief Get the indices array (polygons) of the loaded model.
 *
 * @return A pointer to the indices array.
 */
int *DataModel::GetIndicesArray() const {
  return Object3D::Instance().Indices().data();
}

/**
 * @brief Get a reference to the loaded 3D object model.
 *
 * @return A reference to the 3D object model.
 */
Object3D &DataModel::GetObjectModel() const { return Object3D::Instance(); }

/**
 * @brief Get the value of the coordinates of the farthest point.
 * @return value of the coordinates of the farthest point.
 */
float *DataModel::GetMaximumPoint() const {
  return GetObjectModel().GetMaximumPoint().data();
}

/**
 * @brief Get the value of the coordinates of the closest point.
 * @return value of the coordinates of the closest point.
 */
float *DataModel::GetMinimumPoint() const {
  return GetObjectModel().GetMinimumPoint().data();
}

/**
 * @brief Move the position of the model.
 */
void DataModel::MoveModel(float dx, float dy, float dz) {
  GetObjectModel().Move(dx, dy, dz);
}

/**
 * @brief Rotate the position of the model.
 */
void DataModel::RotateModel(float dx, float dy, float dz) {
  dx *= conversion_factor_;
  dy *= conversion_factor_;
  dz *= conversion_factor_;
  GetObjectModel().Rotate(dx, dy, dz);
}

/**
 * @brief Scale the size of the model.
 */
void DataModel::ScaleModel(float scale_value) {
  GetObjectModel().Scale(scale_value);
}

/**
 * @brief Destructor for the DataModel class.
 */
DataModel::~DataModel() { delete parser_; }
}  // namespace s21
