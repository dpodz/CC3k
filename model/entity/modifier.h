#ifndef MODIFIER_H
#define MODIFIER_H

#include "character.h"
#include <memory>

class Modifier : public Character {

protected:
	std::shared_ptr<Character> mComponent;


public:
	Modifier(std::shared_ptr<Character>);
	virtual ~Modifier() = 0;
};

#endif // MODIFIER_H
