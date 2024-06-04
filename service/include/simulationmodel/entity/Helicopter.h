#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter entity.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Constructs a helicopter object.
   *
   * @param obj JSON object containing the helicopter's information.
   */
  Helicopter(const JsonObject& obj);

  /**
   * @brief Destructor.
   */
  ~Helicopter();

  /**
   * @brief Updates the helicopter's position.
   *
   * @param dt Delta time.
   */
  void update(double dt);

  /**
   * @brief Converts the helicopter object to a JSON representation.
   *
   * @return JsonObject JSON representation of the helicopter.
   */
  JsonObject toJson() const override;

  /**
   * @brief Converts the JSON object to a helicopter object.
   *
   * @param obj JSON object to convert.
   */
  void fromJson(const JsonObject& obj) override;


 private:
  IStrategy* movement = nullptr;
  double distanceTraveled = 0;
  unsigned int mileCounter = 0;
  Vector3 lastPosition;
  Vector3 dest;
};

#endif  // HELICOPTER_H_
