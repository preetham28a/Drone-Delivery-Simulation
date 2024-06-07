#ifndef STRATEGY_FACTORY_H_
#define STRATEGY_FACTORY_H_

#include <string>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Graph.h"
#include "IStrategy.h"

/**
 * @class StrategyFactory
 * @brief Factory class for creating path strategy objects.
 */
class StrategyFactory {
 public:
  /**
   * @brief Creates a path strategy object based on the specified strategy name.
   *
   * @param strategyName Name of the strategy to create.
   * @param start Starting position.
   * @param end Destination position.
   * @param graph Graph representing the map.
   * @return IStrategy* Pointer to the created path strategy object.
   */
  static IStrategy* createStrategy(const std::string& strategyName,
                                   const Vector3& start, const Vector3& end,
                                   const routing::Graph* graph);
};

#endif  // STRATEGY_FACTORY_H_
