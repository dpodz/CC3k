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
	mGrid = mGridInit->generateNewGrid();
}

void Game::createNewEntities() {
	mGridInit->createNewEntities(mGrid);
}

void Game::setFactionRelation(FactionId a, FactionId b, FactionRelation newRelation) {
	mFactionRelation.erase(make_pair(a, b));
	mFactionRelation.insert(make_pair(a, b), newRelation);
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
