#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include "character.h"
#include "baseTreasure.h"

//These need to be declared

class Shade : public Character {
public:
	Shade();
	~Shade();

	int getScore() const override;
	void attack(std::shared_ptr<Character>) override;
};

//Vampire
class Vampire : public Character {
public:
	Vampire();
	~Vampire();
	
	void attack(std::shared_ptr<Character>) override;
};

//Drow
class Drow : public Character {
public:
	Drow();
	~Drow();
	void attack(std::shared_ptr<Character>) override;
};

//Goblin
class Goblin : public Character {
public:
	Goblin();
	~Goblin();
	void onKill() override;
	void attack(std::shared_ptr<Character>) override;
	void getAttackedBy(std::shared_ptr<Orc>) override;
};

//Troll
class Troll : public Character {
public:
	Troll();
	~Troll();

	void attack(std::shared_ptr<Character>) override;
};

//Human
class Human : public Character {
public:
	Human();
	~Human();
	std::vector<std::shared_ptr<Entity>> onDeath() override;
	void attack(std::shared_ptr<Character>) override;
};

//Dwarf
class Dwarf : public Character {
public:
	Dwarf();
	~Dwarf();
	void attack(std::shared_ptr<Character>) override;
};

//Halfling
class Halfling : public Character {
public:
	Halfling();
	~Halfling();
	void attack(std::shared_ptr<Character>) override;
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
	void attack(std::shared_ptr<Character>) override;
};

//Merchant
class Merchant: public Character {
public:
	Merchant();
	~Merchant();
	void attack(std::shared_ptr<Character>) override;
	std::vector<std::shared_ptr<Entity>> onDeath() override;
};

#endif // BASE_CHARACTERS_H
