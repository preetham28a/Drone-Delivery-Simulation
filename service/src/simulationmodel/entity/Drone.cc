#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DataCollector.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"
#include "StrategyFactory.h"

Drone::Drone(const JsonObject& obj) : IEntity(obj) {
  available = true;
  DataCollector::getInstance().recordDroneSpeed(this->getId(), 0);
  DataCollector::getInstance().recordDroneMileage(this->getId(), 0);
  DataCollector::getInstance().recordDrone(this->getId());
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      std::string message = getName() + " heading to: " + package->getName();
      notifyObservers(message);
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
      // Indicate that this drone has started a delivery
      DataCollector::getInstance().startDelivery(this->getId());
      DataCollector::getInstance().startDeliveryTimer(this->getId());
    }
  }
}

void Drone::update(double dt) {
  if (available) getNextDelivery();

  Vector3 previousPosition = this->getPosition();

  if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage && toPackage->isCompleted()) {
      std::string message = getName() + " picked up: " + package->getName();
      notifyObservers(message);
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;

      DataCollector::getInstance().recordPickupTime(this->getId(),
                                                    std::time(nullptr));
      DataCollector::getInstance().recordPickupLocation(this->getId(),
                                                        this->getPosition());
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination && toFinalDestination->isCompleted()) {
      std::string message = getName() + " dropped off: " + package->getName();
      notifyObservers(message);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;

      std::time_t end = std::time(nullptr);
      std::time_t start =
          DataCollector::getInstance().getDeliveryStartTime(this->getId());
      int duration = static_cast<int>(difftime(end, start));
      DataCollector::getInstance().recordDeliveryTime(this->getId(), duration);
      DataCollector::getInstance().recordDropoffTime(this->getId(), end);
      DataCollector::getInstance().recordDropoffLocation(this->getId(),
                                                         this->getPosition());
    }
  }

  if (!available) {
    Vector3 newPosition = this->getPosition();
    double distanceTraveled = (newPosition - previousPosition).magnitude();

    // Update total mileage
    totalMileage += distanceTraveled;
    // Record the speed and mileage for the drone
    double speed = distanceTraveled / dt;  // Calculate the actual speed
    DataCollector::getInstance().recordDroneSpeed(this->getId(), speed);
    DataCollector::getInstance().recordDroneMileage(this->getId(),
                                                    distanceTraveled);
  }
}

JsonObject Drone::toJson() const {
  JsonObject obj;
  obj["id"] = this->getId();
  obj["name"] = this->getName();
  obj["position"] = JsonArray(
      {this->getPosition().x, this->getPosition().y, this->getPosition().z});
  obj["direction"] = JsonArray(
      {this->getDirection().x, this->getDirection().y, this->getDirection().z});
  obj["speed"] = static_cast<double>(this->getSpeed());
  obj["color"] = this->getColor();
  obj["details"] = this->getDetails();

  obj["available"] = available;
  obj["pickedUp"] = pickedUp;

  if (package) {
    obj["packageID"] = package->getId();
  } else {
    obj["packageID"] = -1;
  }

  if (toPackage) {
    obj["toPackageStrategy"] = toPackage->getName();
  } else {
    obj["toPackageStrategy"] = "None";
  }

  if (toFinalDestination) {
    obj["toFinalDestinationStrategy"] = package->getStrategyName();
  } else {
    obj["toFinalDestinationStrategy"] = "None";
  }

  return obj;
}

void Drone::fromJson(const JsonObject& obj) {
  details = obj["details"];
  JsonArray posi = obj["position"];
  Vector3 pos = {posi[0], posi[1], posi[2]};
  this->setPosition(pos);

  JsonArray diri = obj["direction"];
  Vector3 dir = {diri[0], diri[1], diri[2]};
  this->setDirection(dir);

  speed = obj["speed"];
  color = obj["color"].toString();

  available = obj["available"];

  pickedUp = obj["pickedUp"];

  int objid = obj["packageID"];
  if (objid != -1) {
    std::map<int, IEntity*> curr = model->getEntities();
    int packageID = obj["packageID"];
    package = static_cast<Package*>(curr[packageID]);

  } else {
    toPackage = nullptr;
    toFinalDestination = nullptr;
    package = nullptr;
    return;
  }

  const routing::Graph* graph = model->getGraph();

  std::string toFinalDestinationName = obj["toFinalDestinationStrategy"];

  toPackage = new BeelineStrategy(position, package->getPosition());

  if ((toFinalDestinationName.compare("None"))) {
    if (toFinalDestinationName == "astar") {
      toFinalDestination = new JumpDecorator(
          new AstarStrategy(package->getPosition(), package->getDestination(),
                            model->getGraph()));
    } else if (toFinalDestinationName == "dfs") {
      toFinalDestination = new SpinDecorator(new JumpDecorator(
          new DfsStrategy(package->getPosition(), package->getDestination(),
                          model->getGraph())));
    } else if (toFinalDestinationName == "bfs") {
      toFinalDestination = new SpinDecorator(new SpinDecorator(
          new BfsStrategy(package->getPosition(), package->getDestination(),
                          model->getGraph())));
    } else if (toFinalDestinationName == "dijkstra") {
      toFinalDestination = new JumpDecorator(new SpinDecorator(
          new DijkstraStrategy(package->getPosition(),
                               package->getDestination(), model->getGraph())));
    } else {
      toFinalDestination = new BeelineStrategy(package->getPosition(),
                                               package->getDestination());
    }
  }
}
