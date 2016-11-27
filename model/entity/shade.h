#ifndef SHADE_H
#define SHADE_H
#include "character.h"
#include <memory>

class Shade : public Character {
 public:
	Shade();
	~Shade();

	int getScore() const override;
	bool canWalkOn() override;
	void lookedOnBy(std::shared_ptr<Character>) override;
	void attack(std::shared_ptr<Entity>) override;
};

#endif	// SHADE_H
