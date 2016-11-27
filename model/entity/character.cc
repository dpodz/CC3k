#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include "character.h"
#include "stats.h"
#include "../faction.h"

using namespace std;


Character::Character(FactionId factionId, Stats stats, int curHP, int maxHP): 
									mFaction{factionId}, mCharStats{stats}, mCurHP{curHP}, mMaxHP{maxHP} { }

Character::~Character() { }								

int Character::getHealth() const {
	return mCurHP;

}

void Character::setHealth(int hp) {
	mCurHP = hp;
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
}

void Character::onKill() {
	// TODO
}	

void Character::useItem(shared_ptr<Item> item) {
	// TODO
}
