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
#include <cstdlib>

using namespace std;


Character::Character(FactionId factionId, Stats stats, int curHP, int maxHP): 
									mFaction{factionId}, mCharStats(make_shared<StatsContainer>(stats)), mCurHP{curHP}, mMaxHP{maxHP} { }

Character::~Character() { }								

int Character::getHealth() const {
	return mCurHP;
}

void Character::setHealth(int hp) {
	if (hp <= 0) {
		mCurHP = 0;

		CharacterDeath msg {static_pointer_cast<Character>(shared_from_this())};
		notifyObservers(msg);
	} else if ((hp <= mMaxHP && hp > 0) || (hp > 0 && mMaxHP < 0)) { // if mMaxHP < 0 , consider infinite max hp
		mCurHP = hp;
	} else if (hp > mMaxHP) {
		mCurHP = mMaxHP;
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
	auto search = mKnowledge.find(typeid(*entity));

	if (search != mKnowledge.end()) {
		return search->second;
	}
	
	return false;
}

void Character::setKnowledgeOf(shared_ptr<Entity> entity, bool knows) {
	mKnowledge[typeid(*entity)] = knows;
}

FactionId Character::getFaction() const {
	return mFaction;
}

void Character::setFaction(FactionId factionId) {
	mFaction = factionId;
}

bool Character::takeDamage(shared_ptr<Character> attacker){

	if (getStats().dodge * 100 > (rand() % 100)) {
		CharacterAttack msg {attacker, 
			static_pointer_cast<Character>(shared_from_this()), 0, true};
		notifyObservers(msg);
		return false;
	}

	int attackerAtk = attacker->getStats().attack;
	int dmg = ceil((100.0 / ( 100.0+getStats().defence )) * attackerAtk);

	CharacterAttack msg {attacker, 
		static_pointer_cast<Character>(shared_from_this()), dmg, false};
	notifyObservers(msg);

	setHealth( getHealth() - dmg );

	return true;
}

void Character::getAttackedBy(shared_ptr<Vampire> attacker){
	if(takeDamage(attacker)) {
		attacker->setHealth( attacker->getHealth() + 5);	
	}
}

void Character::getAttackedBy(shared_ptr<Drow> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Troll> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Goblin> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Human> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Dwarf> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Halfling> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Elf> attacker){
	takeDamage(attacker);
	if (getHealth() > 0) {
		takeDamage(attacker);
	}
}

void Character::getAttackedBy(shared_ptr<Orc> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Merchant> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Dragon> attacker){
	takeDamage(attacker);
}

void Character::getAttackedBy(shared_ptr<Shade> attacker){
	takeDamage(attacker);
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

void Character::walkedOnBy(shared_ptr<Character>) {}

void Character::turnUpdate() {
	setHealth(getHealth() + mCharStats->getStats().healthRegen);
}

void Character::lookedOnBy(shared_ptr<Character> character) {
	if (static_pointer_cast<Character>(shared_from_this()) != character) {
		
	}
}
