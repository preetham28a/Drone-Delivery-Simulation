#ifndef BEELINE_STRATEGY_H_
#define BEELINE_STRATEGY_H_

#include "PathStrategy.h"

/**
 * @brief This class inherits from the PathStrategy class and is responsible for
 * generating the beeline path that the drone will take.
 */
class BeelineStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Beeline Strategy object.
   *
   * @param position Starting position.
   * @param destination End destination.
   */
  BeelineStrategy(Vector3 pos, Vector3 des);

  /**
   * @brief Get the name of the strategy.
   *
   * @return std::string Name of the strategy.
   */
  std::string getName() const;
};

#endif  // BEELINE_STRATEGY_H_
