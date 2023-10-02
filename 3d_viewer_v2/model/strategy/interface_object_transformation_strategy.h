#ifndef INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_INTERFACE_OBJECT_TRANSFORMATION_STRATEGY_H_
#define INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_INTERFACE_OBJECT_TRANSFORMATION_STRATEGY_H_

#include <array>

namespace s21 {
/**
 * @brief The IObjectTransformationStrategy class is an interface for object
 * transformation strategies.
 */
class IObjectTransformationStrategy {
 public:
  /**
   * @brief Virtual destructor for IObjectTransformationStrategy.
   */
  virtual ~IObjectTransformationStrategy() = default;

  /**
   * @brief Transform the object with a single float parameter.
   * @param scale_value The scale value for the transformation.
   */
  virtual void transform(const float) {}

  /**
   * @brief Transform the object with a std::array of three float parameters.
   * @param args An array of three float parameters for the transformation.
   */
  virtual void transform(const std::array<float, 3>&) {}
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_BUSINESS_LOGIC_STRATEGY_INTERFACE_OBJECT_TRANSFORMATION_STRATEGY_H_
