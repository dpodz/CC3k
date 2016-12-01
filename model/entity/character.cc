#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include <math.h>
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
	if ((hp <= mMaxHP && hp >= 0) || (hp >= 0 && mMaxHP < 0)) {
		mCurHP = hp;
	} else if (hp > mMaxHP) {
		mCurHP = mMaxHP;
	} else if (hp < 0) {
		mCurHP = 0;
	}
}

Stats Character::getStats() const {
	return mCharStats;
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

// Can't use this for double dispatch! Just here for reference.
/*
void Character::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Character>(shared_from_this()), this->getStats().attack);
}

void Character::attack(shared_ptr<Character> defender, int bonusAttack) {
	// bonus attack is extra attack from modifiers
	defender->getAttackedBy(static_pointer_cast<Character>(shared_from_this()), this->getStats().attack + bonusAttack);
}	
*/

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
void Character::getAttackedBy(std::shared_ptr<Elf> attakcer, int attackDamage){
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
	setHealth(getHealth() + mCharStats.healthRegen);
}

void Character::lookedOnBy(shared_ptr<Character> character) {
	if (static_pointer_cast<Character>(shared_from_this()) != character) {
		
	}
}
