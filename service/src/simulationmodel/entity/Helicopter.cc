#define _USE_MATH_DEFINES
#include "Helicopter.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"
#include "StrategyFactory.h"

Helicopter::Helicopter(const JsonObject& obj) : IEntity(obj) {
  this->lastPosition = this->position;
}

Helicopter::~Helicopter() {
  if (movement) delete movement;
}

void Helicopter::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);

    double diff = this->lastPosition.dist(this->position);

    this->lastPosition = this->position;

    this->distanceTraveled += diff;

    if (this->distanceTraveled > 1625.0) {
      std::string message = this->getName() + " has traveled " +
                            std::to_string(++mileCounter) + " miles";
      this->notifyObservers(message);

      this->distanceTraveled = 0;
    }
  } else {
    if (movement) delete movement;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    movement = new BeelineStrategy(position, dest);
  }
}

JsonObject Helicopter::toJson() const {
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

  obj["distanceTraveled"] = static_cast<double>(distanceTraveled);
  obj["mileCounter"] = static_cast<int>(mileCounter);
  JsonArray lastpos = {lastPosition.x, lastPosition.y, lastPosition.z};
  obj["lastPosition"] = lastpos;
  obj["dest"] = JsonArray({dest.x, dest.y, dest.z});

  if (movement) {
    obj["movementStrategy"] = movement->getName();
  }

  return obj;
}

void Helicopter::fromJson(const JsonObject& obj) {
  JsonArray posi = obj["position"];
  Vector3 pos = {posi[0], posi[1], posi[2]};

  this->setPosition(pos);

  JsonArray diri = obj["direction"];
  Vector3 dir = {diri[0], diri[1], diri[2]};
  this->setDirection(dir);

  speed = obj["speed"];

  color = obj["color"].toString();

  distanceTraveled = (obj["distanceTraveled"]);
  int mileCount = obj["mileCounter"];
  mileCounter = static_cast<unsigned int>(mileCount);
  JsonArray lastposi = obj["lastPosition"];
  Vector3 lastpos = {lastposi[0], lastposi[1], lastposi[2]};
  lastPosition = lastpos;

  JsonArray destin = obj["dest"];
  Vector3 desti = {destin[0], destin[1], destin[2]};
  dest = desti;
  movement = new BeelineStrategy(this->position, dest);
}
