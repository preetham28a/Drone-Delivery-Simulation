#ifndef DIJKSTRA_STRATEGY_H_
#define DIJKSTRA_STRATEGY_H_

#include "Graph.h"
#include "PathStrategy.h"

/**
 * @brief This class inherits from the PathStrategy class and is responsible for
 * generating the Dijkstra path that the drone will take.
 */
class DijkstraStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Dijkstra Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DijkstraStrategy(Vector3 position, Vector3 destination,
                   const routing::Graph* graph);

  /**
   * @brief Get the name of the strategy.
   *
   * @return std::string Name of the strategy.
   */
  std::string getName() const;
};
#endif  // DIJKSTRA_STRATEGY_H_
