#ifndef MESSAGES_H
#define MESSAGES_H

#include <memory>
#include <string>
#include "../model/position.h"

class Entity;
class Character;
class Item;
class Game;
class Observer;

// Base class
struct BaseMessage {
	virtual void notifyObserver( std::shared_ptr<Observer> ) = 0;
};

// Debugging Message
struct DebugMessage: public BaseMessage {
	std::string message;
	
	virtual void notifyObserver( std::shared_ptr<Observer> ) override;
};

// Character Death
struct CharacterDeath: public BaseMessage {
	std::shared_ptr<Character> killer;
	std::shared_ptr<Character> killed;

	virtual void notifyObserver( std::shared_ptr<Observer> ) override;
};

// Character Attack
struct CharacterAttack: public BaseMessage {
	std::shared_ptr<Character> attacker;
	std::shared_ptr<Character> defender;
	int damage;

	virtual void notifyObserver( std::shared_ptr<Observer> ) override;
};

// Item Used
struct ItemUsed: public BaseMessage {
	std::shared_ptr<Character> character;
	std::shared_ptr<Item> item;

	virtual void notifyObserver ( std::shared_ptr<Observer>  ) override;
};

// Entity Created
struct EntityCreated: public BaseMessage {
	std::shared_ptr<Entity> entity;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Entity Removed
struct EntityRemoved: public BaseMessage {
	std::shared_ptr<Entity> entity;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Map Created
struct GridCreated: public BaseMessage {
	std::shared_ptr<Game> theGame;

	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Entity Observed
struct EntityObserved: public BaseMessage {
	std::shared_ptr<Character> observer;
	std::shared_ptr<Entity> observed;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Item Picked Up
struct ItemPickedUp: public BaseMessage {
	std::shared_ptr<Character> character;
	std::shared_ptr<Item> item;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Entity Moved
struct EntityMoved: public BaseMessage {
	std::shared_ptr<Entity> entity;
	Position oldPos;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;
};

#endif //MESSAGES_H
