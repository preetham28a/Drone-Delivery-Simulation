#ifndef CELEBRATION_DECORATOR_H_
#define CELEBRATION_DECORATOR_H_

#include "IStrategy.h"

/**
 * @brief This class inherits from the IStrategy class and represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class ICelebrationDecorator : public IStrategy {
 protected:
  IStrategy* strategy = nullptr;
  float time = 0;

 public:
  /**
   * @brief Construct a new Celebration Decorator object.
   *
   * @param[in] strategy The strategy to decorate onto.
   * @param[in] time How long to celebrate.
   */
  ICelebrationDecorator(IStrategy* strategy, double time = 4);

  /**
   * @brief Celebration Destructor.
   */
  virtual ~ICelebrationDecorator();

  /**
   * @brief Move the entity with the behavior as described for a certain time.
   *
   * @param entity Entity to move.
   * @param dt Delta Time.
   */
  virtual void move(IEntity* entity, double dt);

  /**
   * @brief Check if the movement is completed by checking the time.
   *
   * @return True if complete, false if not complete.
   */
  virtual bool isCompleted();

  /**
   * @brief Perform celebration behavior.
   *
   * @param entity Entity to celebrate.
   * @param dt Delta Time.
   */
  virtual void celebrate(IEntity* entity, double dt) = 0;

  /**
   * @brief Get the name of the celebration decorator.
   *
   * @return The name of the celebration decorator.
   */
  virtual std::string getName() const = 0;
};

#endif  // CELEBRATION_DECORATOR_H_
