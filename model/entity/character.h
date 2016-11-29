#ifndef CHARACTER_H
#define CHARACTER_H

#include "stats.h"
#include "entity.h"
#include "../faction.h"
#include <vector>
#include <map>
#include <typeindex>
#include <memory>
#include <typeindex>

class Item;

class Character : public Entity {

	std::map<std::type_index, bool> mKnowledge;
	FactionId mFaction;
	Stats mCharStats;
	int mCurHP;
	int mMaxHP;

public:
	Character(FactionId, Stats, int curHP, int maxHP);
	Character() { }
	~Character();
	
	int getHealth() const;
	void setHealth(int); 

	virtual Stats getStats() const;

	bool hasKnowledgeOf(std::shared_ptr<Entity>) const;
	void setKnowledgeOf(std::shared_ptr<Entity>, bool);

	FactionId getFaction() const;
	void setFaction(FactionId);

	virtual void attack(std::shared_ptr<Entity>);
	// May need to rewrite function below (expand it)
	virtual void getAttackedBy(std::shared_ptr<Entity>);

	virtual int getDroppedGold() const;
	virtual int getScore() const;

	virtual std::vector<std::shared_ptr<Entity>> onDeath();
	virtual void onKill();	

	virtual void useItem(std::shared_ptr<Item>);

	virtual bool canWalkOn() override;
	virtual void walkedOnBy(std::shared_ptr<Character>) override;
	
	virtual void turnUpdate() override;
};

#endif // CHARACTER_H
