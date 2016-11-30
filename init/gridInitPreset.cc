#include "gridInitPreset.h"
#include <cstdlib>
#include <vector>
#include <map>
#include "../model/entity/entity.h"
#include "../model/entity/character.h"
#include "../model/cell.h"
#include "../model/entity/baseTreasure.h"
#include "../model/entity/baseCharacters.h"
#include "../model/entity/basePotions.h"


#define entityMapEntry(symbol, type, args) \
	{symbol, []() -> shared_ptr<Entity> {return make_shared<type>(args);}},

using namespace std;

const map<char, shared_ptr<Entity>(*)()> entityMap {
	entityMapEntry('H', Human, )
	entityMapEntry('W', Dwarf, )
	entityMapEntry('E', Elf, )
	entityMapEntry('O', Orc, )
	entityMapEntry('M', Merchant, )
	entityMapEntry('D', Dragon, )
	entityMapEntry('L', Halfling, )
	entityMapEntry('0', RestoreHealth, )
	entityMapEntry('1', BoostAtk, )
	entityMapEntry('2', BoostDef, )
	entityMapEntry('3', PoisonHealth, )
	entityMapEntry('4', WoundAtk, )
	entityMapEntry('5', WoundDef, )
	entityMapEntry('6', SmallGold, )
	entityMapEntry('7', NormalGold, )
	entityMapEntry('8', MerchantHoard, )
	entityMapEntry('9', DragonHoard, )
};

GridInitPreset::GridInitPreset(shared_ptr<Character> player, const string fileName,
	vector<shared_ptr<Observer>> observers): 
	GridInit {}, mPlayer {player}, mFile {fileName}, mObservers {observers} {}

GridInitPreset::~GridInitPreset() {}

//Public methods

shared_ptr<Grid> GridInitPreset::createGrid() {
	string line;
	GridSize gridSize {79,25};
	auto theGrid = make_shared<Grid>(gridSize);

	// read in the floor plan
	for (int y = 0; y < 25; ++y) {
		getline(mFile, line);
		for (int x = 0 ; x < 79 ; ++x) {
			auto cell = theGrid->getCell({x,y});
			if (line[x] == '|' || line[x] == '-') {
				cell->setType(CellType::Wall);
			} else if (line[x] == '+') {
				cell->setType(CellType::Door);
			} else if (line[x] == '#') {
				cell->setType(CellType::Passage);
			} else if (line[x] != ' ') {
				cell->setType(CellType::Floor);
			}
		}
	}

	// Reset file stream back to beginning
	mFile.seekg(0, std::ios::beg);
	return theGrid;
}

void GridInitPreset::createEntities(shared_ptr<Grid> theGrid) {
	string line;

	for (int y = 0; y < 25; ++y) {
		getline(mFile, line);
		for (int x = 0 ; x < 79 ; ++x) {
			auto cell = theGrid->getCell({x,y});
			auto search = entityMap.find(line[x]);
			if (line[x] == '@') {
				cell->addEntity(mPlayer);
			} else if(search != entityMap.end()) {
				auto newEntity = search->second();
				newEntity->attach(mObservers);
				cell->addEntity(search->second());
			}
		}
	}
}
