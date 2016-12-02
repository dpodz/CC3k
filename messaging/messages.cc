#include "messages.h"
#include "observer.h"
#include <memory>

void DebugMessage::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void InfoMessage::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void CharacterDeath::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void CharacterAttack::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void ItemUsed::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void EntityCreated::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void EntityRemoved::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void GridCreated::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void EntityObserved::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void ItemPickedUp::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}

void EntityMoved::notifyObserver( std::shared_ptr<Observer> observer ) {
	observer->notify(*this);
}
