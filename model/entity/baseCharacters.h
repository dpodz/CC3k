#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include "character.h"

class Shade : public Character {
public:
	Shade();
	~Shade();

	int getScore() const override;
};

//Vampire
class Vampire : public Character {
public:
	Vampire();
	~Vampire();
	
	void attack(std::shared_ptr<Entity>) override;
};

//Drow
class Drow : public Character {
public:
	Drow();
	~Drow();
};

//Goblin
class Goblin : public Character {
public:
	Goblin();
	~Goblin();
	void onKill() override;
};

//Troll
class Troll : public Character {
public:
	Troll();
	~Troll();
};

//Human
class Human : public Character {
public:
	Human();
	~Human();
	std::vector<std::shared_ptr<Entity>> onDeath() override;
};

//Dwarf
class Dwarf : public Character {
public:
	Dwarf();
	~Dwarf();
};

//Halfling
class Halfling : public Character {
public:
	Halfling();
	~Halfling();
	void getAttackedBy(std::shared_ptr<Character>) override;
};

//Elf
class Elf : public Character {
public:
	Elf();
	~Elf();
	void attack(std::shared_ptr<Character>) override;
};

//Orc
class Orc: public Character {
public:
	Orc();
	~Orc();
	void attack(std::shared_ptr<Character>) override;
};

//Dragon
class Dragon: public Character {
	std::shared_ptr<DragonHoard> treasure;
public:
	Dragon();
	~Dragon();
};

//Merchant
class Merchant: public Character {
public:
	Merchant();
	~Merchant();
};
#endif // BASE_CHARACTERS_H
