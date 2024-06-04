#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Human
 * @brief Represents a human entity.
 */
class Human : public IEntity {
 public:
  /**
   * @brief Constructs a human object.
   *
   * @param obj JSON object containing the human's information.
   */
  Human(const JsonObject& obj);

  /**
   * @brief Destructor.
   */
  ~Human();

  /**
   * @brief Updates the human's position.
   *
   * @param dt Delta time.
   */
  void update(double dt);

  /**
   * @brief Converts the human object to a JSON representation.
   *
   * @return JsonObject JSON representation of the human.
   */
  JsonObject toJson() const override;

  /**
   * @brief Converts the JSON object to a human object.
   *
   * @param obj JSON object to convert.
   */
  void fromJson(const JsonObject& obj) override;

 private:
  static Vector3 kellerPosition;
  IStrategy* movement = nullptr;
  bool atKeller = false;
  Vector3 dest;
};

#endif  // HUMAN_H_
