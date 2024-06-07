#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <deque>
#include <map>
#include <set>

#include "CompositeFactory.h"
#include "Drone.h"
#include "Graph.h"
#include "IController.h"
#include "IEntity.h"
#include "IObserver.h"
#include "Robot.h"
#include "SimulationCaretaker.h"
#include "SimulationMemento.h"

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel : public IObserver {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type Graph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::Graph* graph);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(const JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   *
   * @param id of the entity to be removed
   */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(const JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns Graph* graph pointer
   */
  const routing::Graph* getGraph() const;

  /**
   * @brief Notifies about a message.
   *
   * This method notifies about a message by accepting a constant reference to a
   * string.
   *
   * @param message The message to notify about.
   */
  void notify(const std::string& message) const;

  /**
   * @brief Gets the entities.
   *
   * This method returns a map containing integer keys and pointers to IEntity
   * objects as values.
   *
   * @return A map containing integer keys and pointers to IEntity objects as
   * values.
   */
  std::map<int, IEntity*> getEntities();

  /**
   * @brief Saves the simulation state.
   *
   * This method saves the current state of the simulation.
   */
  void saveSimulationState();

  /**
   * @brief Restores the simulation state.
   *
   * This method restores the simulation state to a previously saved state.
   */
  void restoreSimulationState();

  /**
   * @brief Resets the simulation.
   *
   * This method resets the simulation by clearing scheduled deliveries and
   * removing all entities.
   */
  void resetSimulation();

  /**
   * @brief Removes all entities.
   *
   * This method removes all entities from the simulation.
   */
  void removeAllEntities();

  std::deque<Package*> scheduledDeliveries;

 protected:
  /**
   * @brief Removes an entity with the given ID from the simulation
   * @param id ID of the entity to be removed
   */
  void removeFromSim(int id);
  IController& controller;
  std::map<int, IEntity*> entities;
  std::vector<const JsonObject*> trips;
  std::set<int> removed;
  const routing::Graph* graph = nullptr;
  CompositeFactory entityFactory;
  SimulationCaretaker caretaker;
};

#endif  // SIMULATION_MODEL_H_
