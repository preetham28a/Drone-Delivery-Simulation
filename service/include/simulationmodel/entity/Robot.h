#ifndef ROBOT_H_
#define ROBOT_H_

#include <vector>

#include "IEntity.h"
#include "Package.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @class Robot
 * @brief Represents a robot in a physical system.
 *
 * Robots move using Euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param obj JSON object containing the robot's information.
   */
  Robot(const JsonObject& obj);

  /**
   * @brief Updates the robot.
   *
   * @param dt Difference in time since last update.
   */
  void update(double dt);

  /**
   * @brief Receives the passed-in package.
   *
   * @param p Package to be received by the robot.
   */
  void receive(Package* p);

  bool requestedDelivery = true;

  /**
   * @brief Converts the robot object to a JSON representation.
   *
   * @return JsonObject JSON representation of the robot.
   */
  JsonObject toJson() const override;

  /**
   * @brief Converts the JSON object to a robot object.
   *
   * @param obj JSON object to convert.
   */
  void fromJson(const JsonObject& obj) override;


 protected:
  Package* package = nullptr;
};

#endif  // ROBOT_H_
