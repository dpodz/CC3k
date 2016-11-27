#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include "character.h"

class Shade : Character {

public:
	Shade();
	~Shade();

	virtual int getScore() override;
};

#endif // BASE_CHARACTERS_H
