#include "Robot.h"

#include "DataCollector.h"
#include "SimulationModel.h"
#include "vector3.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {
  Vector3 spawnLocation = this->getPosition();
  DataCollector::getInstance().recordRobotSpawnLocation(this->getId(),
                                                        spawnLocation);
}

void Robot::update(double dt) {}

void Robot::receive(Package* p) { package = p; }

JsonObject Robot::toJson() const {
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

  obj["requestedDelivery"] = requestedDelivery;

  if (package) {
    obj["packageID"] = package->getId();
  }

  return obj;
}

void Robot::fromJson(const JsonObject& obj) {
  JsonArray posi = obj["position"];
  Vector3 pos = {posi[0], posi[1], posi[2]};
  this->setPosition(pos);
  JsonArray diri = obj["direction"];
  Vector3 dir = {diri[0], diri[1], diri[2]};
  this->setDirection(dir);
  speed = obj["speed"];
  color = obj["color"].toString();

  requestedDelivery = obj["requestedDelivery"];

  if (obj.contains("packageID")) {
    std::map<int, IEntity*> curr = model->getEntities();
    int packagedID = obj["packageID"];
    package = static_cast<Package*>(curr[packagedID]);
  }
}
