#include "SimulationMemento.h"

SimulationMemento::SimulationMemento(std::vector<const JsonObject*>& obj)
    : objects(obj) {}

SimulationMemento::~SimulationMemento() {
  for (const JsonObject* object : objects) {
    delete object;
  }
}
