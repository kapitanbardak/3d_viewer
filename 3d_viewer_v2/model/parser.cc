#include "parser.h"

namespace s21 {
/**
 * @brief Construct a new Parser:: Parser object.
 *
 * Initializes the parser with the 3D data model instance.
 */
Parser::Parser() : data_3d_(Object3D::Instance()) {}

/**
 * @brief Read and parse a 3D object from a file.
 *
 * @param file_name The name of the file containing the 3D object data.
 */
void Parser::ReadObject(std::string const& file_name) {
  // Check if the file exists
  std::ifstream file(file_name);

  if (!file) {
    throw std::runtime_error("File not found");
  }

  // Check if the file is not empty
  char firstChar;
  file.get(firstChar);
  if (file.eof()) {
    throw std::runtime_error("File is empty");
    file.close();
  }

  // Clear the data vectors in the data model
  data_3d_.Points().clear();
  data_3d_.Indices().clear();
  data_3d_.Edges().clear();

  // Open the file for reading line by line
  std::string line;
  while (std::getline(file, line)) {
    // Handle the line based on its content
    if (line[0] == 'v' && line[1] == ' ') PointCaseHandler_(line);
    if (line[0] == 'f') PolygonCaseHandler_(line);
  }
  file.close();
  if (data_3d_.Points().size() == 0 || data_3d_.Indices().size() == 0) {
    throw std::runtime_error("There is incorrect model in the file");
  }
  data_3d_.SetPath(file_name);
}
/**
 * @brief Handle a line containing vertex data.
 *
 * @param str The line containing vertex data.
 */
void Parser::PointCaseHandler_(std::string& str) {
  int counter = 0;
  float number;
  size_t i = 0, size = str.size();
  while (i < size) {
    if (str[i] == ' ') {
      number = std::stof(str.substr(++i));
      data_3d_.AddPoint(number);
      ++counter;
    }
    ++i;
  }
  if (counter != 3) throw std::runtime_error("Point is wrong: " + str);
}

/**
 * @brief Handle a line containing polygon data.
 *
 * @param str The line containing polygon data.
 */
void Parser::PolygonCaseHandler_(std::string& str) {
  int number, input_iter, previous_polygon_element = -1,
                          first_polygon_element = -1;
  size_t i = 0, size = str.size() - 1;
  while (i < size) {
    if (str[i] == ' ' && i + 1 < size && str[i + 1] != '\n') {
      number = std::stoi(str.substr(++i));
      --number;
      input_iter = 2;
      if (first_polygon_element < 0) {
        input_iter = 1;
        first_polygon_element = number;
      }
      if (previous_polygon_element >= 0)
        data_3d_.AddEdge(previous_polygon_element, number);
      previous_polygon_element = number;
      for (int i = 0; i < input_iter; ++i) data_3d_.AddPolygonUnit(number);
    }
    ++i;
  }
  if (first_polygon_element >= 0) {
    data_3d_.AddPolygonUnit(first_polygon_element);
    data_3d_.AddEdge(first_polygon_element, previous_polygon_element);
  } else {
    throw std::runtime_error("Polygon is wrong: " + str);
  }
}
}  // namespace s21
