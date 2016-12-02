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

	DebugMessage(std::string a) : 
		BaseMessage{}, message(a) {}
};

// Info Message
struct InfoMessage: public BaseMessage {
	std::string message;
	
	virtual void notifyObserver( std::shared_ptr<Observer> ) override;

	InfoMessage(std::string a) : 
		BaseMessage{}, message(a) {}
};

// Character Death
struct CharacterDeath: public BaseMessage {
	std::shared_ptr<Character> killer;
	std::shared_ptr<Character> killed;

	virtual void notifyObserver( std::shared_ptr<Observer> ) override;

	CharacterDeath(std::shared_ptr<Character> a, std::shared_ptr<Character> b) : 
		BaseMessage{}, killer(a), killed(b) {}
};

// Character Attack
struct CharacterAttack: public BaseMessage {
	std::shared_ptr<Character> attacker;
	std::shared_ptr<Character> defender;
	int damage;
	bool isMiss;

	virtual void notifyObserver( std::shared_ptr<Observer> ) override;

	CharacterAttack(std::shared_ptr<Character> a, std::shared_ptr<Character> b, int c, bool d) : 
		BaseMessage{}, attacker(a), defender(b), damage{c}, isMiss{d} {}
};

// Item Used
struct ItemUsed: public BaseMessage {
	std::shared_ptr<Character> character;
	std::shared_ptr<Item> item;

	virtual void notifyObserver ( std::shared_ptr<Observer>  ) override;

	ItemUsed(std::shared_ptr<Character> a, std::shared_ptr<Item> b) : 
		BaseMessage{}, character(a), item(b) {}
};

// Entity Created
struct EntityCreated: public BaseMessage {
	std::shared_ptr<Entity> entity;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;

	EntityCreated(std::shared_ptr<Entity> a) :
		BaseMessage {}, entity(a) {}
};

// Entity Removed
struct EntityRemoved: public BaseMessage {
	std::shared_ptr<Entity> entity;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;

	EntityRemoved(std::shared_ptr<Entity> a) :
		BaseMessage {}, entity(a) {}
};

// Map Created
struct GridCreated: public BaseMessage {
	std::shared_ptr<Game> theGame;

	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;

	GridCreated(std::shared_ptr<Game> a) :
		BaseMessage {}, theGame(a) {}
};

// Entity Observed
struct EntityObserved: public BaseMessage {
	std::shared_ptr<Character> observer;
	std::shared_ptr<Entity> observed;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;

	EntityObserved(std::shared_ptr<Character> a, std::shared_ptr<Entity> b) :
		BaseMessage {}, observer(a), observed(b) {}
};

// Item Picked Up
struct ItemPickedUp: public BaseMessage {
	std::shared_ptr<Character> character;
	std::shared_ptr<Item> item;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;

	ItemPickedUp(std::shared_ptr<Character> a, std::shared_ptr<Item> b) : 
		BaseMessage{}, character(a), item(b) {}
};

// Entity Moved
struct EntityMoved: public BaseMessage {
	std::shared_ptr<Entity> entity;
	Position oldPos;
	
	virtual void notifyObserver ( std::shared_ptr<Observer> ) override;

	EntityMoved(std::shared_ptr<Entity> a, Position b) : 
		BaseMessage{}, entity(a), oldPos(b) {}
};

#endif //MESSAGES_H
