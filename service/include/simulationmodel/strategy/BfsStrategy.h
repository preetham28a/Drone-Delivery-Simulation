#ifndef BFS_STRATEGY_H_
#define BFS_STRATEGY_H_

#include "Graph.h"
#include "PathStrategy.h"

/**
 * @brief This class inherits from the PathStrategy class and is responsible for
 * generating the breadth-first search path that the drone will take.
 */
class BfsStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Breadth-First Search Strategy object.
   *
   * @param position Current position.
   * @param destination End destination.
   * @param graph Graph/Nodes of the map.
   */
  BfsStrategy(Vector3 position, Vector3 destination,
              const routing::Graph* graph);

  /**
   * @brief Get the name of the strategy.
   *
   * @return std::string Name of the strategy.
   */
  std::string getName() const;
};
#endif  // BFS_STRATEGY_H_
