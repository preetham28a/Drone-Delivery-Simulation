#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 pos, Vector3 des)
    : PathStrategy({pos, des}) {}

std::string BeelineStrategy::getName() const { return "beeline"; }
