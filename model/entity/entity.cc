#include <memory>
#include "entity.h"


Entity::Entity() { }

Entity::~Entity() { }

int Entity::getGold() const {
	return mGold;
}

void Entity::setGold(int amount) {
	mGold = amount;
}
