#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "Graph.h"
#include "IPublisher.h"
#include "json.h"
#include "math/vector3.h"
#include "util/json.h"

class SimulationModel;

/**
 * @class IEntity
 * @brief Represents an entity in a physical system.
 *
 * An IEntity object has a unique ID, a position, a direction, a destination,
 * and details. It also has a speed, which determines how fast the entity moves
 * in the physical system. Subclasses of IEntity can override the `Update`
 * function to implement their own movement behavior.
 */
class IEntity : public IPublisher {
 public:
  /**
   * @brief Constructor that assigns a unique ID to the entity.
   */
  IEntity();

  /**
   * @brief Constructor with JsonObject details to define the entity
   */
  IEntity(const JsonObject& details);

  /**
   * @brief Virtual destructor for IEntity.
   */
  virtual ~IEntity();

  /**
   * @brief Resets the static currentId counter to 0.
   */
  static void resetCurrentId();

  /**
   * @brief Links this entity to a simulation model,
   *  giving it access to the model's public variables
   *  and functions.
   * @param[in] model The simulation model to link.
   */
  virtual void linkModel(SimulationModel* model);

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int getId() const;

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual Vector3 getPosition() const;

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual Vector3 getDirection() const;

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  virtual const JsonObject& getDetails() const;

  /**
   * @brief Gets the color of the entity
   * @return The color of the entity
   */
  virtual std::string getColor() const;

  /**
   * @brief Gets the name of the entity
   * @return The name of the entity
   */
  virtual std::string getName() const;

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual double getSpeed() const;

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void setPosition(Vector3 pos_);

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void setDirection(Vector3 dir_);

  /**
   * @brief Sets the color of the entity
   * @param col_ The new color of the entity
   */
  virtual void setColor(std::string col_);

  /**
   * @brief Rotate the entity around y axis.
   * @param angle The angle to rotate the entity by.
   */
  virtual void rotate(double angle);

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   */
  virtual void update(double dt) = 0;

  /**
   * @brief Converts the entity to a JsonObject.
   * @return The JsonObject representation of the entity.
   */
  virtual JsonObject toJson() const = 0;

  /**
   * @brief Initializes the entity from a JsonObject.
   * @param obj The JsonObject containing the entity data.
   */
  virtual void fromJson(const JsonObject& obj) = 0;


 protected:
  SimulationModel* model = nullptr; /**< Pointer to the simulation model */
  int id = -1;                      /**< Unique ID of the entity */
  JsonObject details;               /**< Details of the entity */
  Vector3 position;                 /**< Position of the entity */
  Vector3 direction;                /**< Direction of the entity */
  std::string color;                /**< Color of the entity */
  std::string name;                 /**< Name of the entity */
  double speed = 0;                 /**< Speed of the entity */
  static int currentId; /**< Static counter for generating unique IDs */
};

#endif  // ENTITY_H_
