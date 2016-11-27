#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include "character.h"

class Shade : public Character {

public:
	Shade();
	~Shade();

	int getScore() const override;
	void lookedOnBy(std::shared_ptr<Character>) override;
        void attack(std::shared_ptr<Entity>) override;
};

#endif // BASE_CHARACTERS_H
