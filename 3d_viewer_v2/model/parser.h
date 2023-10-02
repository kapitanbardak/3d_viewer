#ifndef INC_3DVIEWER_V2_0_SRC_PARSER_H_
#define INC_3DVIEWER_V2_0_SRC_PARSER_H_

#include <fstream>
#include <stdexcept>
#include <string>

#include "object_3d.h"

namespace s21 {
/**
 * @brief The Parser class is responsible for parsing 3D object data from a file
 * and populating the Object3D instance.
 */
class Parser {
 public:
  /**
   * @brief Constructor for the Parser class.
   */
  Parser();

  /**
   * @brief Read the 3D object data from the specified file and populate the
   * Object3D instance.
   * @param file_name The name of the file to read the object data from.
   */
  void ReadObject(std::string const& file_name);

 private:
  /**
   * @brief Handle the case when a line in the file represents a point.
   * @param str The line containing point data.
   */
  inline void PointCaseHandler_(std::string& str);

  /**
   * @brief Handle the case when a line in the file represents a polygon.
   * @param str The line containing polygon data.
   */
  inline void PolygonCaseHandler_(std::string& str);

  Object3D& data_3d_; /**< Reference to the Object3D instance for storing the
                         parsed object data. */
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_PARSER_H_
