#include "SimulationModel.h"

#include "DataCollector.h"
#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.addFactory(new DroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
}

SimulationModel::~SimulationModel() {
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(const JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.createEntity(entity)) {
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    myNewEntity->addObserver(this);
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

void SimulationModel::resetSimulation() {
  this->removeAllEntities();
  caretaker.clear();
}
void SimulationModel::removeAllEntities() {
  std::set<int> entityIds;
  for (const auto& entityPair : entities) {
    entityIds.insert(entityPair.first);
  }

  for (int id : entityIds) {
    removeFromSim(id);
  }
  IEntity::resetCurrentId();
}

void SimulationModel::scheduleTrip(const JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }

  trips.push_back(new JsonObject(details));
}

const routing::Graph* SimulationModel::getGraph() const { return graph; }

void SimulationModel::setGraph(const routing::Graph* graph) {
  if (this->graph) delete this->graph;
  this->graph = graph;
}

void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

void SimulationModel::notify(const std::string& message) const {
  JsonObject details;
  details["message"] = message;
  this->controller.sendEventToView("Notification", details);
}

void SimulationModel::saveSimulationState() {
  std::vector<const JsonObject*> objects;
  for (auto& [id, entity] : entities) {
    objects.push_back(new JsonObject(entity->toJson()));
  }
  SimulationMemento* memento = new SimulationMemento(objects);
  caretaker.saveState(memento);
}

void SimulationModel::restoreSimulationState() {
  SimulationMemento* memento = caretaker.restoreState();
  if (memento) {
    std::set<int> mementoIds;
    for (const JsonObject* obj : memento->getObjects()) {
      int objid = (*obj)["id"];
      mementoIds.insert(objid);
    }

    std::vector<int> idsToRemove;
    for (auto& [id, entity] : entities) {
      if (mementoIds.find(id) == mementoIds.end()) {
        idsToRemove.push_back(id);
      }
    }

    for (int id : idsToRemove) {
      removeFromSim(id);
    }

    for (const JsonObject* obj : memento->getObjects()) {
      int objid = (*obj)["id"];
      if (entities.find(objid) != entities.end()) {
        entities[objid]->fromJson(*obj);
      }
    }
    delete memento;
  }
}

std::map<int, IEntity*> SimulationModel::getEntities() { return entities; }

void SimulationModel::stop(void) {
  DataCollector::getInstance().outputDataToCSV();
  DataCollector::getInstance().outputMoreDataToCSV();
}
