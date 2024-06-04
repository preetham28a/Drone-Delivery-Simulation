#include "DijkstraStrategy.h"

#include "Dijkstra.h"

DijkstraStrategy::DijkstraStrategy(Vector3 pos, Vector3 des,
                                   const routing::Graph* g) {
  if (g) {
    path = g->getPath(pos, des, routing::Dijkstra()).value();
    auto y = path.back().y;
    path.push_back(Vector3(des.x, y, des.z));
  } else {
    path = {pos, des};
  }
}

std::string DijkstraStrategy::getName() const { return "bijkstra"; }
