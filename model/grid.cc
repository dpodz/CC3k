#include "grid.h"
#include "cell.h"
#include "entity/item.h"
#include "entity/character.h"
#include "../messaging/observer.h"
#include "../messaging/subject.h"
#include "../messaging/messages.h"
#include <memory>
#include <vector>
#include <exception>

using namespace std;

Grid::Grid(GridSize size) : Observer {}, Subject {}, mSize (size), 
	mCells (mSize.x, 
		vector<shared_ptr<Cell>> (mSize.y, make_shared<Cell>())) {}

Grid::~Grid() {}

void Grid::turnUpdate() {
	for (auto & row : mCells) {
		for (auto & entity : row) {
			entity->turnUpdate();
		}
	}
}

GridSize Grid::getGridSize() const {
	return mSize;
}

std::shared_ptr<Cell> Grid::getCell(Position pos) const {
	return getCell(pos.x, pos.y);
}

std::shared_ptr<Cell> Grid::getCell(int x, int y) const {
	return mCells.at(x).at(y);
}

bool Grid::checkBounds(Position pos) {
	return 0 <= pos.x && pos.x < mSize.x 
		&& 0 <= pos.y && pos.y < mSize.y;
}

void Grid::move(shared_ptr<Character> character, Direction dir) {
	Position oldPos = character->getPos();
	Position newPos = oldPos.calcPosInDirection(dir);

	if (!checkBounds(newPos)) {
		throw out_of_range("Move");
	}

	getCell(oldPos)->removeEntity(character);
	getCell(newPos)->addEntity(character);
	character->setPos(newPos);

	EntityMoved msg(character, oldPos);

	notifyObservers(msg);

	// Let character observe area around it
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			Position viewPos = {i + newPos.x, j + newPos.y};
			if (checkBounds(viewPos)) { 
				getCell(viewPos)->lookedOn(character);
			}
		}
	}
}

void Grid::attack(shared_ptr<Character> attacker, Direction dir) {
	Position attackerPos = attacker->getPos();
	Position defenderPos = attackerPos.calcPosInDirection(dir);

	if (!checkBounds(defenderPos)) {
		throw out_of_range("Attack");
	}

	shared_ptr<Character> defender = getCell(defenderPos)->getCharacter();

	attacker->attack(defender);
}

void Grid::usePotion(shared_ptr<Character> character, Direction dir) {
	Position charPos = character->getPos();
	Position potPos = charPos.calcPosInDirection(dir);

	if (!checkBounds(potPos)) {
		throw out_of_range("usePotion");
	}

	getCell(potPos)->usePotion(character);
}

void Grid::notify(CharacterDeath & msg) {
	getCell(msg.killed->getPos())->removeEntity(msg.killed);
}

void Grid::notify(ItemPickedUp & msg) {
	getCell(msg.item->getPos())->removeEntity(msg.item);
}
