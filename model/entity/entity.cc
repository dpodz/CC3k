#include <memory>
#include "entity.h"


Entity::Entity(int gold, Position pos): 
	mGold {gold}, mCurPos (pos) {}

Entity::~Entity() { }

int Entity::getGold() const {
	return mGold;
}

void Entity::setGold(int amount) {
	mGold = amount;
}

Position Entity::getPos() const {
	return mCurPos;
}

void Entity::setPos(Position pos) {
	mCurPos = pos;
}

bool Entity::canWalkOn() { return false; }

// Nothing happens by default
void Entity::turnUpdate() { }
