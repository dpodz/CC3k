#ifndef CHARACTER_H
#define CHARACTER_H

#include "stats.h"
#include "entity.h"
#include "../faction.h"
#include <vector>
#include <map>
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
	Character(Stats, int maxHP, FactionId);
	~Character();
	
	int getHealth() const;
	void setHealth(int); 

	virtual Stats getStats() const;

	bool hasKnowledgeOf(std::shared_ptr<Entity>) const;
	void setKnowledgeOf(std::shared_ptr<Entity>, bool);

	FactionId getFaction() const;
	void setFaction(FactionId);

	virtual void attack(std::shared_ptr<Entity>) = 0;
	// May need to rewrite function below (expand it)
	virtual void getAttackedBy(std::shared_ptr<Entity>);

	virtual void getDroppedGold() const;
	virtual int getScore() const;

	virtual std::vector<std::shared_ptr<Entity>> onDeath();
	virtual void onKill();	

	virtual void useItem(std::shared_ptr<Item>);
};

#endif // CHARACTER_H
