#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include "character.h"
#include "stats.h"
#include "../faction.h"
#include "potion.h"

using namespace std;


Character::Character(FactionId factionId, Stats stats, int curHP, int maxHP): 
									mFaction{factionId}, mCharStats(stats), mCurHP{curHP}, mMaxHP{maxHP} { }

Character::~Character() { }								

int Character::getHealth() const {
	return mCurHP;

}

void Character::setHealth(int hp) {
	if (hp <= mMaxHP && hp >= 0) {
		mCurHP = hp;
	}
}

Stats Character::getStats() const {
	return mCharStats;
}

bool Character::hasKnowledgeOf(shared_ptr<Entity> entity) const {
	return mKnowledge.find(typeid(entity))->second;
}

void Character::setKnowledgeOf(shared_ptr<Entity> entity, bool knows) {
	mKnowledge[typeid(entity)] = knows;
}

FactionId Character::getFaction() const {
	return mFaction;
}

void Character::setFaction(FactionId factionId) {
	mFaction = factionId;
}

void Character::attack(shared_ptr<Entity> entity) {
	// TODO
}

void Character::getAttackedBy(shared_ptr<Entity> entity) {
	// TODO
}

int Character::getDroppedGold() const {
	return getGold();
}

int Character::getScore() const {
	return getGold();
}

vector<shared_ptr<Entity>> Character::onDeath() {
	// TODO
	return vector<shared_ptr<Entity>>();
}

void Character::onKill() {
	// TODO
}	

void Character::useItem(shared_ptr<Item> item) {
	item->itemUsedBy(shared_ptr<Character>(this));	
}

bool Character::canWalkOn() { return false; }

void Character::walkedOnBy(std::shared_ptr<Character>) {}

void Character::turnUpdate() {
	setHealth(getHealth() + mCharStats.healthRegen);
}

void Character::lookedOnBy(shared_ptr<Character> character) {
	// TODO
}
