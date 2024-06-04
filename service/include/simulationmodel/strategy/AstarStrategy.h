#ifndef ASTAR_STRATEGY_H_
#define ASTAR_STRATEGY_H_

#include "Graph.h"
#include "PathStrategy.h"

/**
 * @brief This class inherits from the PathStrategy class and is responsible for
 * generating the A* path that the drone will take.
 */
class AstarStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new A* Strategy object.
   *
   * @param position Current position.
   * @param destination End destination.
   * @param graph Graph/Nodes of the map.
   */
  AstarStrategy(Vector3 position, Vector3 destination,
                const routing::Graph* graph);

  /**
   * @brief Get the name of the strategy.
   *
   * @return std::string Name of the strategy.
   */
  std::string getName() const;
};
#endif  // ASTAR_STRATEGY_H_
