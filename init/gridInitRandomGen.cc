#include "gridInitRandomGen.h"
#include "../model/entity/entity.h"
#include "../model/entity/character.h"
#include "../model/cell.h"
#include <fstream>
#include <memory>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

GridInitRandomGen::GridInitRandomGen(shared_ptr<Character> player, const string fileName,
	vector<shared_ptr<Observer>> observers): 
	GridInit {}, mPlayer {player}, mFile {fileName}, mObservers {observers}, mRooms {} {}

GridInitRandomGen::~GridInitRandomGen() {}

//Private methods

shared_ptr<Entity> GridInitRandomGen::getRandomEntity(vector< shared_ptr<Entity> > entityVector) {
	return entityVector.at(rand() % entityVector.size());
}

void GridInitRandomGen::generateRoom(int roomNumber, int posx, int posy, shared_ptr<Grid> theGrid) {

	if (posx >= 0 && posx < 79 && posy >= 0 && posy < 25 && 
		theGrid->getCell(posx,posy)->getType() == CellType::Floor &&
		theGrid->getCell(posx,posy)->getRoomId() == -1) {
		// Add this grid to the rooms list and recurse
		theGrid->getCell(posx,posy)->setRoomId(roomNumber);
		mRooms[roomNumber].push_back(theGrid->getCell(posx,posy));
		// recurse through the 4 adjacent cells
		generateRoom(roomNumber, posx+1, posy, theGrid);
		generateRoom(roomNumber, posx-1, posy, theGrid);
		generateRoom(roomNumber, posx, posy-1, theGrid);
		generateRoom(roomNumber, posx, posy+1, theGrid);
	}
}

//Public methods

shared_ptr<Grid> GridInitRandomGen::createGrid() {
/*if (!mFile.isOpen()){
		throw "cannot open file";
	}*/

	string line;
	int lineNum = 0;
	GridSize gridSize {79,25};
	auto theGrid = make_shared<Grid>(gridSize);

	// read in the floor plan
	while (getline(mFile, line)) {
			for (int i = 0 ; i < 79 ; i++) {
				auto cell = theGrid->getCell({i,lineNum});
				if (line[i] == '|' || line[i] == '-') {
					cell->setType(CellType::Wall);
				} else if (line[i] == '.') {
					cell->setType(CellType::Floor);
				} else if (line[i] == '+') {
					cell->setType(CellType::Door);
				} else if (line[i] == '#') {
					cell->setType(CellType::Passage);
				}
			}
			lineNum++;
	}

	// We need to generate a list of the rooms:
	mRooms.clear(); // make sure it's empty
	int roomNumber = 0;

	for (int i = 0 ; i < 79 ; i++) {
		for (int j = 0 ; j < 25; j++) {
			if (theGrid->getCell(i,j)->getType() == CellType::Floor &&
			    theGrid->getCell(i,j)->getRoomId() == -1) {
				mRooms.emplace_back();
				this->generateRoom(roomNumber,i,j,theGrid);
				roomNumber++;
			}
		}
	}

	return theGrid;
}

void GridInitRandomGen::createEntities(shared_ptr<Grid> theGrid) {
	
	// Generate the player
	int playerRoom = rand() % mRooms.size();
	auto playerCell = mRooms[playerRoom][rand() % mRooms[playerRoom].size()];
	mPlayer->setPos(playerCell->getPos());
	playerCell->addEntity(mPlayer);
	
	// Generate the stairway location
	int stairRoom;
	while ((stairRoom = rand()%mRooms.size()) ==  playerRoom);
	mRooms[stairRoom][rand() % mRooms[stairRoom].size()]->setType(CellType::Stair);
	
	// Generate 10 potions
	/*
	for (int i = 0 ; i < 10 ; i++) {
		vector<std::shared_ptr<Entity>> potionList;
		potionList.push_back(std::shared_ptr<Entity>(new RestoreHealth));
		potionList.push_back(std::shared_ptr<Entity>(new PoisonHealth));
		potionList.push_back(std::shared_ptr<Entity>(new BoostAttack));
		potionList.push_back(std::shared_ptr<Entity>(new WoundAttack));
		potionList.push_back(std::shared_ptr<Entity>(new BoostDefence));
		potionList.push_back(std::shared_ptr<Entity>(new WoundDefence));
	}
	*/
}
