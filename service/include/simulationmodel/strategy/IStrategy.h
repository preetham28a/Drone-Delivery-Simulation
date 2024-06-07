#ifndef I_STRATEGY_H_
#define I_STRATEGY_H_

#include "IEntity.h"

/**
 * @brief Strategy interface
 *
 * This interface defines the basic structure for implementing different
 * strategies for moving entities within a system.
 */
class IStrategy {
 public:
  /**
   * @brief Destructor.
   *
   * Virtual destructor to ensure proper cleanup when derived classes are
   * deleted.
   */
  virtual ~IStrategy() {}

  /**
   * @brief Move toward next position.
   *
   * This method is responsible for moving the given entity towards its next
   * position based on the implemented strategy.
   *
   * @param entity Entity to move.
   * @param dt Delta Time.
   */
  virtual void move(IEntity* entity, double dt) = 0;

  /**
   * @brief Check if the trip is completed.
   *
   * This method checks whether the movement trip initiated by the strategy
   * implementation is completed.
   *
   * @return True if complete, false if not complete.
   */
  virtual bool isCompleted() = 0;

  /**
   * @brief Get the name of the strategy.
   *
   * This method returns the name of the strategy implemented by the derived
   * class.
   *
   * @return Name of the strategy.
   */
  virtual std::string getName() const = 0;
};

#endif
