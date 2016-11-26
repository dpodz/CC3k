#ifndef ENTITY_H
#define ENTITY_H

#include "../../messaging/subject.h"
#include "character.h"
#include <memory>

class Entity : public Subject {

	int mGold;

public:
	Entity();
	~Entity();

	int getGold() const;
	void setGold(int);

	virtual bool canWalkOn();
	virtual void lookedOnBy(std::shared_ptr<Character>) = 0;
};

#endif // ENTITY_H
