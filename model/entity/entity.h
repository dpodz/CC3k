#ifndef ENTITY_H
#define ENTITY_H

#include "../../messaging/subject.h"
#include <memory>

class Character;

class Entity : public Subject {

	int mGold;
	Position mCurPos;

public:
	Entity(int gold = 0, Position pos = {-1,-1});
	~Entity();

	int getGold() const;
	void setGold(int);

	Position getPos() const;
	void setPos(Position);

	virtual bool canWalkOn();
	virtual void lookedOnBy(std::shared_ptr<Character>) = 0;
	virtual void walkedOnBy(std::shared_ptr<Character>) = 0;

	virtual void turnUpdate();
};

#endif // ENTITY_H
