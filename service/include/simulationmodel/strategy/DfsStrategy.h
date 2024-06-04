#ifndef DFS_STRATEGY_H_
#define DFS_STRATEGY_H_

#include "Graph.h"
#include "PathStrategy.h"

/**
 * @brief This class inherits from the PathStrategy class and is responsible for
 * generating the depth-first search path that the drone will take.
 */
class DfsStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Depth-First Search Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DfsStrategy(Vector3 position, Vector3 destination,
              const routing::Graph* graph);

  /**
   * @brief Get the name of the strategy.
   *
   * @return std::string Name of the strategy.
   */
  std::string getName() const;
};
#endif  // DFS_STRATEGY_H_
