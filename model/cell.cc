#include "cell.h"
#include "../messaging/subject.h"
#include <memory>
#include <vector>

using namespace std;

Cell::Cell() : 
	mEntities {}, mCellType {CellType::Empty} {}

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

shared_ptr<Character> Cell::getCharacter() const {
	
}

bool Cell::isValidMove() const {

}

void Cell::addEntity(shared_ptr<Entity> entity) {
	mEntities.push_back(entity);
}

void Cell::removeEntity(shared_ptr<Entity> entity) {
	mEntities.erase(remove(mEntities.begin(), mEntities.end(), 
		entity), mEntities.end());
}

void Cell::walkedOn(shared_ptr<Character>) {

}

void Cell::usePotion(shared_ptr<Character>) {

}

void Cell::turnUpdate() {

}
