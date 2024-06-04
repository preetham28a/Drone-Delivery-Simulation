#include "SimulationCaretaker.h"

void SimulationCaretaker::saveState(SimulationMemento* memento) {
  mementos.push(memento);
}

SimulationMemento* SimulationCaretaker::restoreState() {
  if (!mementos.empty()) {
    SimulationMemento* memento = mementos.top();
    mementos.pop();
    return memento;
  }
  return nullptr;
}
void SimulationCaretaker::clear() {
  while (!mementos.empty()) {
    delete mementos.top();
    mementos.pop();
  }
}
SimulationCaretaker::~SimulationCaretaker() { this->clear(); }
