#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include <math.h>
#include "character.h"
#include "baseCharacters.h"
#include "stats.h"
#include "../faction.h"
#include "potion.h"
#include "../../messaging/subject.h"
#include "../../messaging/messages.h"

using namespace std;


Character::Character(FactionId factionId, Stats stats, int curHP, int maxHP): 
									mFaction{factionId}, mCharStats(make_shared<StatsContainer>(stats)), mCurHP{curHP}, mMaxHP{maxHP} { }

Character::~Character() { }								

int Character::getHealth() const {
	return mCurHP;

}

void Character::setHealth(int hp) {
	if ((hp <= mMaxHP && hp >= 0) || (hp >= 0 && mMaxHP < 0)) {
		mCurHP = hp;
	} else if (hp > mMaxHP) {
		mCurHP = mMaxHP;
	} else if (hp < 0) {
		mCurHP = 0;
	}
}

Stats Character::getStats() const {
	return mCharStats->getStats();
}

shared_ptr<StatsContainer> Character::getStatsContainer() const {
	return mCharStats;
}

void Character::setStatsContainer(shared_ptr<StatsContainer> statsContainer) {
	mCharStats = statsContainer;
}

bool Character::hasKnowledgeOf(shared_ptr<Entity> entity) const {
	auto search = mKnowledge.find(typeid(entity));

	if (search != mKnowledge.end()) {
		return search->second;
	}
	
	return false;
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

void Character::takeDamage(int damage){
	this->setHealth( this->getHealth() - ceil((100.0 / ( 100.0+this->getStats().defence )) * damage) );
}

void Character::getAttackedBy(std::shared_ptr<Vampire> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Drow> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Troll> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Goblin> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Human> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Dwarf> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Halfling> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Elf> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Orc> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Merchant> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Dragon> attacker, int attackDamage){
	this->takeDamage(attackDamage);
}
void Character::getAttackedBy(std::shared_ptr<Shade> attacker, int attackDamage){
	this->takeDamage(attackDamage);

	auto self = static_pointer_cast<Character>(shared_from_this());

	CharacterAttack msg {attacker, self, attackDamage};
	notifyObservers(msg);

}

int Character::getDroppedGold() const {
	return getGold();
}

int Character::getScore() const {
	return getGold();
}

vector<shared_ptr<Entity>> Character::onDeath() {
	return vector<shared_ptr<Entity>>();
}

void Character::onKill() {}	

void Character::useItem(shared_ptr<Item> item) {
	item->itemUsedBy(static_pointer_cast<Character>(shared_from_this()));	
}

bool Character::canWalkOn() { return false; }

void Character::walkedOnBy(std::shared_ptr<Character>) {}

void Character::turnUpdate() {
	setHealth(getHealth() + mCharStats->getStats().healthRegen);
}

void Character::lookedOnBy(shared_ptr<Character> character) {
	if (static_pointer_cast<Character>(shared_from_this()) != character) {
		
	}
}
