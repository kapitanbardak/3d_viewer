#ifndef VIEWER_CORE_INTERNAL_NAMES_H
#define VIEWER_CORE_INTERNAL_NAMES_H

namespace s21 {
/**
 * @enum VertexType
 * @brief Enum representing types of vertices.
 *
 * This enum defines three vertices types: Transparent, Hard and Smooth.
 * Use this enum to specify the type of vertices in your code.
 */
enum class VertexType { kTransparent = 0, kHard = 1, kSmooth = 2 };

/**
 * @enum RibsType
 * @brief Enum representing types of ribs.
 *
 * This enum defines two ribs types: Dotted and Line.
 * Use this enum to specify the type of ribs in your code.
 */
enum class RibsType { kDotted = 3, kLine = 4 };

/**
 * @enum ProjectionType
 * @brief Enum representing types of projections.
 *
 * This enum defines two projection types: Parallel and Central.
 * Use this enum to specify the type of projection in your code.
 */
enum class ProjectionType {
  kParallel = 0, /**< Parallel projection. */
  kCentral = 1   /**< Central projection. */
};

/**
 * @enum ChangeTypeMode
 * @brief Enum representing functions mode types.
 *
 * This enum defines 7 types: Vertex ,Ribs, Background, Rotate, Move, Scale and
 * Grid.
 */
enum class FunctionsMode {
  kVertex = 0,
  kRibs = 1,
  kBackground = 2,
  kRotate = 3,
  kMove = 4,
  kScale = 5,
  kGrid = 6
};

/**
 * @brief The Names enum
 * @brief Enum representing buttons names.
 *
 * This enum defines names of 13 buttons from MainWindow.
 */
enum class Names {
  kBackgroundColor = 0,
  kRibsColor = 1,
  kVertexColor = 2,
  kLoadObject = 3,
  kDefaultPosition = 4,
  kPicture = 5,
  kGif = 6,
  kVertexSize = 7,
  kRibsSize = 8,
  kVertexType = 9,
  kRibsType = 10,
  kParallelMode = 11,
  kCentralMode = 12,
  kGridColor = 13
};
}  // namespace s21
#endif  // VIEWER_CORE_INTERNAL_NAMES_H
