#ifndef DEFAULT_MESSAGES_H
#define DEFAULT_MESSAGES_H

#include <memory>
#include "messages.h"

// Default messages need to know that these exist
class Observer;
class Entity;
class Character;
class Item;
class Game;
struct Position;

// Debugging Message
struct DebugMessage: public BaseMessage {
	std::string message;
	
	void notifyObserver( std::shared_ptr<Observer> ) override;
};

// Character Death
struct CharacterDeath: public BaseMessage {
	std::shared_ptr<Character> killer;
	std::shared_ptr<Character> killed;

	void notifyObserver( std::shared_ptr<Observer> ) override;
};

// Character Attack
struct CharacterAttack: public BaseMessage {
	std::shared_ptr<Character> attacker;
	std::shared_ptr<Character> defender;
	int damage;

	void notifyObserver( std::shared_ptr<Observer> ) override;
};

// Item Used
struct ItemUsed: public BaseMessage {
	std::shared_ptr<Character> character;
	std::shared_ptr<Item> item;

	void notifyObserver ( std::shared_ptr<Observer>  ) override;
};

// Entity Created
struct EntityCreated: public BaseMessage {
	std::shared_ptr<Entity> entity;
	Position pos;
	
	void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Entity Removed
struct EntityRemoved: public BaseMessage {
	std::shared_ptr<Entity> entity;
	Position pos;
	
	void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Map Created
struct MapCreated: public BaseMessage {
	std::shared_ptr<Game> theGame;

	void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Entity Observed
struct EntityObserved: public BaseMessage {
	std::shared_ptr<Character> observer;
	std::shared_ptr<Entity> observed;
	
	void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Item Picked Up
struct ItemPickedUp: public BaseMessage {
	std::shared_ptr<Character> character;
	std::shared_ptr<Item> item;
	
	void notifyObserver ( std::shared_ptr<Observer> ) override;
};

// Entity Moved
struct EntityMoved: public BaseMessage {
	std::shared_ptr<Entity> entity;
	Position oldPos;
	Position newPos;
	
	void notifyObserver ( std::shared_ptr<Observer> ) override;
};
