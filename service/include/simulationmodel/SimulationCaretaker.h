// SimulationCaretaker.h
#ifndef SIMULATION_CARETAKER_H_
#define SIMULATION_CARETAKER_H_

#include <stack>

#include "SimulationMemento.h"

/**
 * @brief The SimulationCaretaker class manages the mementos of a simulation.
 */
class SimulationCaretaker {
 private:
  /**
   * @brief Stack to store the mementos.
   */
  std::stack<SimulationMemento*> mementos;

 public:
  /**
   * @brief Saves the state represented by the provided memento.
   * @param memento The memento to save.
   */
  void saveState(SimulationMemento* memento);

  /**
   * @brief Restores the last saved state.
   * @return The memento representing the restored state.
   */
  SimulationMemento* restoreState();

  /**
   * @brief Clears all saved states.
   */
  void clear();

  /**
   * @brief Destructor to free memory.
   */
  ~SimulationCaretaker();
};

#endif  // SIMULATION_CARETAKER_H_
