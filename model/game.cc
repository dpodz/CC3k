#include "game.h"
#include "grid.h"
#include "faction.h"
#include "../init/gridInit.h"
#include <memory>
#include <map>
#include <utility>

using namespace std;

Game::Game() : 
	mGrid {}, mGridInit {}, mFactionRelation {} {}
	
Game::~Game() {}
	
void Game::setGridGen(shared_ptr<GridInit> gridInit) {
	mGridInit = gridInit;
}

void Game::generateNewGrid() {
	mGrid = mGridInit->createGrid();
}

void Game::createNewEntities() {
	mGridInit->createEntities(mGrid);
}

shared_ptr<Grid> Game::getGrid() const {
	return mGrid;
}

void Game::attach(vector<shared_ptr<Observer>> observers) {
	mGrid->attach(observers);
	mGrid->attachCells(observers);
}

void Game::setFactionRelation(FactionId a, FactionId b, FactionRelation newRelation) {
	auto key = make_pair(a, b);
	mFactionRelation.erase(key);
	mFactionRelation.insert({key, newRelation});
}

FactionRelation Game::getFactionRelation(FactionId a, FactionId b) const {
	auto search = mFactionRelation.find(make_pair(a, b));

	if (search != mFactionRelation.end()) {
		return search->second;
	}
	else {
		return FactionRelation::neutral;
	}
}

void Game::turnUpdate() {
	if (mGrid) {
		mGrid->turnUpdate();
	}
}

GridSize Game::getGridSize() const {
	return mGrid->getGridSize();
}

shared_ptr<Cell> Game::getCell(Position pos) const {
	return mGrid->getCell(pos);
}

shared_ptr<Cell> Game::getCell(int x, int y) const {
	return mGrid->getCell(x, y);
}

void Game::move(std::shared_ptr<Character> character, Direction dir) {
	mGrid->move(character, dir);
}

void Game::attack(std::shared_ptr<Character> character, Direction dir) {
	mGrid->attack(character, dir);
}

void Game::usePotion(std::shared_ptr<Character> character, Direction dir) {
	mGrid->usePotion(character, dir);
}
