#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"
#include "StrategyFactory.h"

Vector3 Human::kellerPosition(64.0, 254.0, -210.0);

Human::Human(const JsonObject& obj) : IEntity(obj) {}

Human::~Human() {
  if (movement) delete movement;
}

void Human::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
    bool nearKeller = this->position.dist(Human::kellerPosition) < 85;
    if (nearKeller && !this->atKeller) {
      std::string message = this->getName() + " visited Keller hall";
      notifyObservers(message);
    }
    atKeller = nearKeller;
  } else {
    if (movement) delete movement;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }
}

JsonObject Human::toJson() const {
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

  obj["atKeller"] = atKeller;
  obj["dest"] = JsonArray({dest.x, dest.y, dest.z});

  if (movement) {
    obj["movementStrategy"] = movement->getName();
  }

  return obj;
}

void Human::fromJson(const JsonObject& obj) {
  JsonArray posi = obj["position"];
  Vector3 pos = {posi[0], posi[1], posi[2]};
  this->setPosition(pos);
  JsonArray diri = obj["direction"];
  Vector3 dir = {diri[0], diri[1], diri[2]};
  this->setDirection(dir);
  speed = obj["speed"];
  color = obj["color"].toString();

  atKeller = obj["atKeller"];
  JsonArray destin = obj["dest"];
  Vector3 desti = {destin[0], destin[1], destin[2]};
  dest = desti;
  const routing::Graph* graph = model->getGraph();
  if (obj.contains("movementStrategy")) {
    std::string movementStrategyName = obj["movementStrategy"];
    Vector3 currentPosition = getPosition();
    movement = StrategyFactory::createStrategy(movementStrategyName,
                                               currentPosition, dest, graph);
  }
}
