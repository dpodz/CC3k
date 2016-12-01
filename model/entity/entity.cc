#include <memory>
#include "entity.h"
#include "../../messaging/messages.h"
#include "../../messaging/subject.h"

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

void Entity::lookedOnBy(std::shared_ptr<Character> character) {
	EntityObserved msg {character, shared_from_this()};
	notifyObservers(msg);
}

void Entity::walkedOnBy(std::shared_ptr<Character> character) { }

// Nothing happens by default
void Entity::turnUpdate() { }
