#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;

/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Constructs a drone object.
   *
   * @param obj JSON object containing the drone's information.
   */
  Drone(const JsonObject& obj);

  /**
   * @brief Destructor.
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler.
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position.
   *
   * @param dt Delta time.
   */
  void update(double dt);

  // Deleting copy constructor and assignment operator to prevent copying.
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Converts the drone object to a JSON representation.
   *
   * @return JsonObject JSON representation of the drone.
   */
  JsonObject toJson() const override;

  /**
   * @brief Converts the JSON object to a drone object.
   *
   * @param obj JSON object to convert.
   */
  void fromJson(const JsonObject& obj) override;


 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  double totalMileage = 0;  // To store the total mileage of the drone
};

#endif  // DRONE_H_
