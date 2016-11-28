#include "gridInitPreset.h"
#include <cstdlib>
#include <vector>

using namespace std;

GridInitPreset::GridInitPreset(shared_ptr<Character> player, const String fileName): 
	mPlayer{player}, mFile(fileName, ifstream::in) {}

GridInitPreset::~GridInitPreset() {}

void GridInitPreset::generateRoom(int roomNumber, int posx, int posy, shared_ptr<Grid> theGrid) {

}

//Public methods

shared_ptr<Grid> GridInitPreset::createGrid() {

}

void createEntities(shared_ptr<Grid> theGrid) {

	// TODO: Work on this
}
