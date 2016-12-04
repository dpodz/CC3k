#include "gridInitRandomGen.h"
#include "../model/entity/entity.h"
#include "../model/entity/character.h"
#include "../model/cell.h"
#include "../model/position.h"
#include "../model/entity/baseTreasure.h"
#include "../model/entity/baseCharacters.h"
#include "../model/entity/basePotions.h"
#include <fstream>
#include <memory>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

#define singleEntityGen(type, args) \
	[]() -> vector<shared_ptr<Entity>> {return vector<shared_ptr<Entity>>{make_shared<type>(args)};},

const vector<vector<shared_ptr<Entity>>(*)()> potionList {
	singleEntityGen(BoostAtk, )
	singleEntityGen(WoundAtk, )
	singleEntityGen(BoostDef, )
	singleEntityGen(WoundDef, )
	singleEntityGen(RestoreHealth, )
	singleEntityGen(PoisonHealth, )
};

const vector<vector<shared_ptr<Entity>>(*)()> treasureList {
	singleEntityGen(SmallGold, )
	singleEntityGen(SmallGold, )
	singleEntityGen(SmallGold, )
	singleEntityGen(SmallGold, )
	singleEntityGen(SmallGold, )
	singleEntityGen(NormalGold, )
	singleEntityGen(NormalGold, )
	[]() -> vector<shared_ptr<Entity>> {
		auto dragon = make_shared<Dragon>();
		auto dragonHoard = make_shared<DragonHoard>();
		dragon->setHoard(dragonHoard);
		dragonHoard->setDragon(dragon);
		return vector<shared_ptr<Entity>>{dragonHoard, dragon};
	}
};

const vector<vector<shared_ptr<Entity>>(*)()> characterList {
	singleEntityGen(Human, )
	singleEntityGen(Human, )
	singleEntityGen(Human, )
	singleEntityGen(Human, )
	singleEntityGen(Dwarf, )
	singleEntityGen(Dwarf, )
	singleEntityGen(Dwarf, )
	singleEntityGen(Halfling, )
	singleEntityGen(Halfling, )
	singleEntityGen(Halfling, )
	singleEntityGen(Halfling, )
	singleEntityGen(Halfling, )
	singleEntityGen(Elf, )
	singleEntityGen(Elf, )
	singleEntityGen(Orc, )
	singleEntityGen(Orc, )
	singleEntityGen(Merchant, )
	singleEntityGen(Merchant, )
};


GridInitRandomGen::GridInitRandomGen(shared_ptr<Character> player, 
	const string fileName, shared_ptr<vector<weak_ptr<Observer>>> observers): 
	GridInit {}, mPlayer {player}, mFile {fileName}, mObservers {observers}, mRooms {} {}

GridInitRandomGen::~GridInitRandomGen() {}

void GridInitRandomGen::generateEntities(
	vector<vector<shared_ptr<Entity>>(*)()> entityVector, 
	int total, shared_ptr<Grid> grid) {
	for (int i = 0; i < total; ++i) {

		// Generates the entities to place
		auto entities = entityVector.at(rand() % entityVector.size())();
		if (entities.size() == 0) return;

		// Assuming no room is ever filled up completely
		auto roomToGen = mRooms.at(rand() % mRooms.size());

		shared_ptr<Cell> cellToUse;

		do {
			cellToUse = roomToGen.at(rand() % roomToGen.size());
		} while(cellToUse->getEntities().size() != 0 
			|| cellToUse->getType() == CellType::Stair);

		Position cellPos = cellToUse->getPos();
		vector<shared_ptr<Cell>> possibleLocations;

		for (int x = -1; x <= 1; x++) { 
			for (int y = -1; y <= 1; y++) { 
				if (x != 0 || y !=0) { 
					Position newPos {cellPos.x + x, cellPos.y + y};
					shared_ptr<Cell> newCell = grid->getCell(newPos);

					if (newCell->isValidMove() &&
						newCell->getType() != CellType::Door &&
						newCell->getEntities().size() == 0) {
						possibleLocations.push_back(newCell);
					}
				}
			}
		}

		for (auto & entity: entities) {
			entity->attach(*mObservers);

			if (cellToUse->getEntities().size() == 0
				|| possibleLocations.size() == 0) {
				cellToUse->addEntity(entity);
			}
			else {
				int offset = rand() % possibleLocations.size();
				auto location = possibleLocations.at(offset);
				location->addEntity(entity);

				possibleLocations.erase(possibleLocations.begin() + offset);
			}
		}
	}
}

void GridInitRandomGen::generateRoom(int roomNumber, int posx, 
	int posy, shared_ptr<Grid> theGrid) {

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
	playerCell->addEntity(mPlayer);
	
	// Generate the stairway location
	// Remove prior stairway

	for (int x = 0; x < 79; ++x) {
		for (int y = 0; y < 25; ++y) {
			if (theGrid->getCell(x,y)->getType() == CellType::Stair) {
				theGrid->getCell(x,y)->setType(CellType::Floor);
			}
		}
	}

	int stairRoom;
	do {
		stairRoom = rand() % mRooms.size();
	} while(stairRoom == playerRoom);

	mRooms[stairRoom][rand() % mRooms[stairRoom].size()]->setType(CellType::Stair);
	
	generateEntities(potionList, 10, theGrid);

	generateEntities(treasureList, 10, theGrid);

	generateEntities(characterList, 20, theGrid);
}
