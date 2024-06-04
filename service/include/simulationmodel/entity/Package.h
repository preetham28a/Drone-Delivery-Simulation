#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class Robot;

/**
 * @class Package
 * @brief Represents a package entity.
 */
class Package : public IEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param obj JSON object containing the package's information.
   */
  Package(const JsonObject& obj);

  /**
   * @brief Gets the package's destination.
   *
   * @return The package's destination.
   */
  virtual Vector3 getDestination() const;

  /**
   * @brief Returns the name of the strategy for this package.
   *
   * @returns String name of strategy.
   */
  virtual std::string getStrategyName() const;

  /**
   * @brief Returns the owner of the package.
   *
   * @return Pointer to Robot owning the package.
   */
  virtual Robot* getOwner() const;

  /**
   * @brief Returns whether or not the package needs to be delivered.
   *
   * @return Boolean value indicating if the package requires delivery.
   */
  virtual bool requiresDelivery() const;

  /**
   * @brief Set the strategy name.
   *
   * @param strategyName_ Strategy name.
   */
  virtual void setStrategyName(std::string strategyName_);

  /**
   * @brief Updates the package.
   *
   * @param dt Difference in time since last update.
   */
  virtual void update(double dt);

  /**
   * @brief Sets the attributes for delivery.
   *
   * @param owner Robot for the package to be delivered to.
   */
  virtual void initDelivery(Robot* owner);

  /**
   * @brief Gives the robot/owner this package.
   */
  virtual void handOff();

  /**
   * @brief Converts the package object to a JSON representation.
   *
   * @return JsonObject JSON representation of the package.
   */
  JsonObject toJson() const override;

  /**
   * @brief Converts the JSON object to a package object.
   *
   * @param obj JSON object to convert.
   */
  void fromJson(const JsonObject& obj) override;


 protected:
  bool requiresDelivery_ = true;
  Vector3 destination;
  std::string strategyName;
  Robot* owner = nullptr;
};

#endif  // PACKAGE_H_
