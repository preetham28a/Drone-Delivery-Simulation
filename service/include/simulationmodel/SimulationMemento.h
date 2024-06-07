#ifndef SIMULATION_MEMENTO_H_
#define SIMULATION_MEMENTO_H_

#include <vector>

#include "IEntity.h"

/**
 * @brief A class representing a memento for simulation state.
 *
 * This class holds a collection of JSON objects representing the state of
 * entities in the simulation.
 */
class SimulationMemento {
 private:
  std::vector<const JsonObject*> objects;

 public:
  /**
   * @brief Constructs a SimulationMemento object.
   *
   * Constructs a SimulationMemento object with the given vector of JSON
   * objects.
   *
   * @param obj A vector containing pointers to JSON objects representing the
   * state of entities.
   */
  SimulationMemento(std::vector<const JsonObject*>& obj);

  /**
   * @brief Destroys the SimulationMemento object.
   *
   * Destroys the SimulationMemento object and releases any resources associated
   * with it.
   */
  ~SimulationMemento();

  /**
   * @brief Gets the collection of JSON objects.
   *
   * Returns the collection of JSON objects representing the state of entities
   * in the simulation.
   *
   * @return A constant reference to a vector containing pointers to JSON
   * objects representing the state of entities.
   */
  const std::vector<const JsonObject*>& getObjects() const { return objects; }
};

#endif  // SIMULATION_MEMENTO_H_
