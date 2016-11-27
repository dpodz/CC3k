#include "grid.h"
#include "cell.h"
#include "entity/character.h"
#include "../messaging/observer.h"
#include "../messaging/subject.h"
#include <memory>
#include <vector>

using namespace std;

Grid::Grid(GridSize) : mSize {GridSize}, 
	mCells {GridSize.x, 
		vector<shared_ptr<Cell>> {GridSize.y, make_shared<Cell>()}} {}

Grid::~Grid() {}

void Grid::turnUpdate() {
	for (auto row & : mCells) {
		for (auto entity & : row) {
			entity->turnUpdate();
		}
	}
}

GridSize Grid::getGridSize() const {
	return mSize;
}

std::shared_ptr<Cell> Grid::getCell(int x, int y) const {
	return mCells.at(x, y);
}

// TODO: Below stuff

void Grid::move(std::shared_ptr<Character>, Direction) {

}

void Grid::attack(std::shared_ptr<Character>, Direction) {

}

void Grid::usePotion(std::shared_ptr<Character>, Direction) {

}
