#include "StrategyFactory.h"

IStrategy* StrategyFactory::createStrategy(const std::string& strategyName,
                                           const Vector3& start,
                                           const Vector3& end,
                                           const routing::Graph* graph) {
  if (strategyName == "Astar") {
    return new AstarStrategy(start, end, graph);
  } else if (strategyName == "Bfs") {
    return new BfsStrategy(start, end, graph);
  } else if (strategyName == "Dfs") {
    return new DfsStrategy(start, end, graph);
  } else if (strategyName == "Dijkstra") {
    return new DijkstraStrategy(start, end, graph);
  } else if (strategyName == "Beeline") {
    return new BeelineStrategy(start, end);
  } else {
    return nullptr;
  }
}
