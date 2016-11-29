#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <memory>

class Character;

class Item : public Entity {

public:
	Item();
	virtual ~Item() = 0;

	virtual bool canWalkOn() override;

	virtual void itemUsedBy(std::shared_ptr<Character>);
};

#endif // ITEM_H
