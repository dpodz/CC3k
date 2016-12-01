#ifndef CHARACTER_H
#define CHARACTER_H

#include "stats.h"
#include "entity.h"
#include "../faction.h"
#include <vector>
#include <map>
#include <typeindex>
#include <memory>

class Item;
class Vampire;
class Drow;
class Troll;
class Goblin;
class Human;
class Dwarf;
class Halfling;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Shade;

class Character : public Entity {

	std::map<std::type_index, bool> mKnowledge;
	FactionId mFaction;
	std::shared_ptr<StatsContainer> mCharStats;

	int mCurHP;
	int mMaxHP;
protected:	
	// So we can call this in the overloaded getAttackedBy() method
	void takeDamage(std::shared_ptr<Character>);

public:
	Character(FactionId, Stats, int curHP, int maxHP);
	Character() { }
	~Character();
	
	virtual int getHealth() const;
	virtual void setHealth(int); 

	virtual Stats getStats() const;
	virtual std::shared_ptr<StatsContainer> getStatsContainer() const;
	virtual void setStatsContainer(std::shared_ptr<StatsContainer>);

	bool hasKnowledgeOf(std::shared_ptr<Entity>) const;
	void setKnowledgeOf(std::shared_ptr<Entity>, bool);

	FactionId getFaction() const;
	void setFaction(FactionId);

	virtual void attack(std::shared_ptr<Character>) = 0;
	// Overloading for different classes
	virtual void getAttackedBy(std::shared_ptr<Vampire>);
	virtual void getAttackedBy(std::shared_ptr<Drow>);
	virtual void getAttackedBy(std::shared_ptr<Troll>);
	virtual void getAttackedBy(std::shared_ptr<Goblin>);
	virtual void getAttackedBy(std::shared_ptr<Human>);
	virtual void getAttackedBy(std::shared_ptr<Dwarf>);
	virtual void getAttackedBy(std::shared_ptr<Halfling>);
	virtual void getAttackedBy(std::shared_ptr<Elf>);
	virtual void getAttackedBy(std::shared_ptr<Orc>);
	virtual void getAttackedBy(std::shared_ptr<Merchant>);
	virtual void getAttackedBy(std::shared_ptr<Dragon>);
	virtual void getAttackedBy(std::shared_ptr<Shade>);

	virtual int getDroppedGold() const;
	virtual int getScore() const;

	virtual std::vector<std::shared_ptr<Entity>> onDeath();
	virtual void onKill();	

	virtual void useItem(std::shared_ptr<Item>);

	virtual bool canWalkOn() override;
	virtual void walkedOnBy(std::shared_ptr<Character>) override;
	
	virtual void turnUpdate() override;

	virtual void lookedOnBy(std::shared_ptr<Character>) override;
};

#endif // CHARACTER_H
