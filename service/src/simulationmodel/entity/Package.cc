#include "Package.h"

#include "Robot.h"
#include "SimulationModel.h"

Package::Package(const JsonObject& obj) : IEntity(obj) {
  this->destination = destination;
  this->strategyName = strategyName;
  this->requiresDelivery_ = requiresDelivery_;
}

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

Robot* Package::getOwner() const { return owner; }

bool Package::requiresDelivery() const { return requiresDelivery_; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery_ = false;
  destination = owner->getPosition();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

JsonObject Package::toJson() const {
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

  obj["destination"] =
      JsonArray({getDestination().x, getDestination().y, getDestination().z});
  obj["strategyName"] = this->getStrategyName();
  obj["requiresDelivery"] = requiresDelivery_;

  if (owner) {
    obj["ownerID"] = owner->getId();
  }

  return obj;
}

void Package::fromJson(const JsonObject& obj) {
  JsonArray posi = obj["position"];
  Vector3 pos = {posi[0], posi[1], posi[2]};
  this->setPosition(pos);
  JsonArray diri = obj["direction"];
  Vector3 dir = {diri[0], diri[1], diri[2]};
  this->setDirection(dir);
  speed = obj["speed"];
  color = obj["color"].toString();

  JsonArray desti = obj["destination"];
  Vector3 dest = {desti[0], desti[1], desti[2]};
  destination = dest;
  strategyName = obj["strategyName"].toString();
  requiresDelivery_ = obj["requiresDelivery"];

  if (obj.contains("ownerID")) {
    std::map<int, IEntity*> curr = model->getEntities();
    int ownerID = obj["ownerID"];
    owner = static_cast<Robot*>(curr[ownerID]);
    initDelivery(owner);
  }
}
