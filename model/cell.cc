#include "cell.h"
#include "entity/entity.h"
#include "entity/character.h"
#include "entity/potion.h"
#include "../messaging/subject.h"
#include "exception.h"
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

Cell::Cell() : 
	Subject {}, mEntities {}, mCellType {CellType::Empty} {}

Cell::~Cell() {}

vector<shared_ptr<Entity>> Cell::getEntities() const {
	return mEntities;
}

CellType Cell::getType() const {
	return mCellType;
}

void Cell::setType(CellType cellType) {
	mCellType = cellType;
}

RoomId Cell::getRoomId() const {
	return mRoomId;
}

void Cell::setRoomId(RoomId roomId) {
	mRoomId = roomId;
}

shared_ptr<Character> Cell::getCharacter() const {
	for (auto & entity: mEntities) {
		auto character = dynamic_pointer_cast<Character>(entity);
		if (character.use_count() != 0) {
			return character;
		}
	}
	throw EntityNotFound("Character");
}

bool Cell::isValidMove() const {
	if (mCellType == CellType::Wall || mCellType == CellType::Empty) {
		return false;
	}

	for (auto & entity : mEntities) {
		if (!entity->canWalkOn()) {
			return false;
		}
	}

	return true;
}

void Cell::addEntity(shared_ptr<Entity> entity) {
	mEntities.push_back(entity);

	EntityCreated msg(entity);
	notifyObservers(msg);
}

void Cell::removeEntity(shared_ptr<Entity> entity) {

	auto it = find(mEntities.begin(), mEntities.end(), entity);
	if(it != mEntities.end())
		mEntities.erase(it);

	EntityRemoved msg(entity);
	notifyObservers(msg);
}

void Cell::walkedOn(shared_ptr<Character> character) {
	for (auto & entity : mEntities) {
		entity->walkedOnBy(character);
	}
}

void Cell::lookedOn(shared_ptr<Character> character) {
	for (auto & entity : mEntities) {
		entity->lookedOnBy(character);
	}
}

void Cell::usePotion(shared_ptr<Character> character) {
	for (auto & entity: mEntities) {
		auto potion = dynamic_pointer_cast<Potion>(entity);
		if (potion.use_count() != 0) {
			character->useItem(potion);
			return;
		}
	}
	throw EntityNotFound("Potion");
}

void Cell::turnUpdate() {
	for (auto & entity : mEntities) {
		entity->turnUpdate();
	}
}
