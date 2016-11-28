#include "gridInitPreset.h"
#include <cstdlib>

GridInitPreset::GridInitPreset(std::shared_ptr<Character> player, const std::String fileName): 
	mPlayer{player}, mFile(fileName, std::ifstream::in) {}

GridInitPreset::~GridInitPreset() {}

//Private methods

std::shared_ptr<Entity> GridInitPreset::getRandomEntity(vector<std::shared_ptr<Entity>> entityVector) {
	return entityVector.at(rand()%entityVector.size());
}

void GridInitPreset::generateRoom(int roomNumber, int posx, int posy, std::shared_ptr<Grid> theGrid) {
	if (posx >= 0 && posx < 79 && posy >= 0 && posy < 30 && 
		theGrid->getCell(posx,posy)->getType == CellType::Floor &&
		theGrid->getCell(posx,posy)->getRoomId == -1) {
		// Add this grid to the rooms list and recurse
		theGrid->getCell(posx,posy)->setRoomId(roomNumber);
		mRooms[roomNumber].push_back(theGrid->getCell(posx,posy));
		// recurse through the 4 adjacent cells
		for (int i = -1 ; i <= 1 ; i++) {
			for (int j = -1 ; j <= 1 ; j++) {
				if (i+j%2 == 1) { // this will only iterate on the 4 blocks around the cell
					this->generateRoom(roomNumber, posx+i, posy+j, theGrid);
				}
			}
		}
	}
}

//Public methods

std::shared_ptr<Grid> GridInitPreset::createGrid() {
	if (!mFile.isOpen()){
		throw "cannot open file";
	}
	std::string line;
	int lineNum = 0;
	std::unique_ptr<Grid> theGrid({79,30});
	// read in the floor plan
	while (getline(mFile, line)) {
			for (int i = 0 ; i < 79 ; i++) {
				if (line[i] == '|' || line[i] == '-') {
					theGrid->getCell({i,lineNum})->setType(CellType::Wall);
				} else if (line[i] == '.') {
					theGrid->getCell({i,lineNum})->setType(CellType::Floor);
				} else if (line[i] == '+') {
					theGrid->getCell({i,lineNum})->setType(CellType::Door);
				} else if (line[i] == '#') {
					theGrid->getCell({i,lineNum})->setType(CellType::Passage);
				}
			}
			lineNum++;
	}
	return theGrid;
}

void createEntities(std::shared_ptr<Grid> theGrid) {
	//We need to generate a list of the rooms:
	mRooms.clear(); // make sure it's empty
	int roomNumber = 0;
	for (int i = 0 ; i < 79 ; i++) {
		for (int j = 0 ; j < 30; j++) {
			if (theGrid->getCell(i,j)->getType == CellType::Floor &&
			    theGrid->getCell(i,j)->getRoomId == -1) {
				this->generateRoom(roomNumber,i,j,theGrid);
				roomNumber++;
			}
		}
	}
	//first, generate the player
	int playerRoom = rand() % mRooms.size();
	mRooms[playerRoom][rand() % mRooms[playerRoom].size()]->addEntity(mPlayer);
	
	//next, generate the stairway location
	int stairRoom;
	while ((stairRoom = rand()%mRooms.size()) ==  playerRoom);
	mRooms[stairRoom][rand() % mRooms[stairRoom].size()]->setType(CellType::Stair);
	
	//Next, generate 10 potions
	for (int i = 0 ; i < 10 ; i++) {
		vector<std::shared_ptr<Entity>> potionList;
		potionList.push_back(std::shared_ptr<Entity>(new RestoreHealth));
		potionList.push_back(std::shared_ptr<Entity>(new PoisonHealth));
		potionList.push_back(std::shared_ptr<Entity>(new BoostAttack));
		potionList.push_back(std::shared_ptr<Entity>(new WoundAttack));
		potionList.push_back(std::shared_ptr<Entity>(new BoostDefence));
		potionList.push_back(std::shared_ptr<Entity>(new WoundDefence));
		int posx,posy;
		while (mRooms[(pos
