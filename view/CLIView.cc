#include "CLIView.h"
#include "../model/grid.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <stdlib.h>
#include <typeindex>
#include "../model/entity/treasure.h"
#include "../model/entity/potion.h"
#include "../model/entity/baseCharacters.h"
#include "../model/entity/basePotions.h"
#include "../model/entity/baseTreasure.h"

using namespace std;

struct entityInfo {
	char mapIcon;
	string name;
	string unknownName;
};

const map<type_index, entityInfo> entityInfoMap {
	{typeid(Shade), {'?', "Shade", "Shade"}},
	{typeid(Vampire), {'?', "Vampire", "Vampire"}},
	{typeid(Drow), {'?', "Drow", "Drow"}},
	{typeid(Goblin), {'?', "Goblin", "Goblin"}},
	{typeid(Troll), {'?', "Troll", "Troll"}},
	{typeid(Human), {'H', "Human", "Human"}},
	{typeid(Dwarf), {'W', "Dwarf", "Dwarf"}},
	{typeid(Elf), {'E', "Elf", "Elf"}},
	{typeid(Orc), {'O', "Orc", "Orc"}},
	{typeid(Merchant), {'M', "Merchant", "Merchant"}},
	{typeid(Dragon), {'D', "Dragon", "Dragon"}},
	{typeid(Halfling),{'L', "Halfling", "Halfling"}},
	{typeid(Potion), {'P', "Potion", "Potion"}},
	{typeid(RestoreHealth), {'P', "Restore Health", "Potion"}},
	{typeid(BoostAtk), {'P', "Boost Attack", "Potion"}},
	{typeid(BoostDef), {'P', "Boost Defence", "Potion"}},
	{typeid(PoisonHealth), {'P', "Poison Health", "Potion"}},
	{typeid(WoundAtk), {'P', "Wound Attack", "Potion"}},
	{typeid(WoundDef), {'P', "Wound Defence", "Potion"}},
	{typeid(Treasure), {'G', "Treasure", "Treasure"}},
	{typeid(SmallGold), {'G', "Small Gold", "Small Gold"}},
	{typeid(NormalGold), {'G', "Normal Gold", "Normal Gold"}},
	{typeid(MerchantHoard), {'G', "Merchant Hoard", "Merchant Hoard"}},
	{typeid(DragonHoard), {'G', "Dragon Hoard", "Dragon Hoard"}}
};

const map<Direction, string> directionStringMap {
	{ Direction::NO, "NO"}, 
	{ Direction::SO, "SO"}, 
	{ Direction::EA, "EA"}, 
	{ Direction::WE, "WE"}, 
	{ Direction::NE, "NE"},
	{ Direction::NW, "NW"},
	{ Direction::SE, "SE"},
	{ Direction::SW, "SW"}
};

CLIView::CLIView(shared_ptr<Character> player, shared_ptr<Game> game):
	mPlayer {player}, mGame {game}, mMessages {}, mLevel {1} {}

CLIView::~CLIView() {}

bool CLIView::checkIfVerticalWall(int x, int y) {

	if (y > 0 ) {
		if (mGame->getCell(x,y-1)->getType() == CellType::Wall) {
			return true;
		}
	}

	if (y < mGame->getGridSize().y - 1) {
		if (mGame->getCell(x,y+1)->getType() == CellType::Wall) {
			return true;
		}
	}

	return false;
}

void CLIView::printGrid() {

	if (!mGame) {
		cout << "No grid loaded yet" << endl;
		return;
	}

	GridSize gridSize = mGame->getGridSize();

	for (int y = 0 ; y < gridSize.y ; ++y) {
		for (int x = 0 ; x < gridSize.x ; ++x) {
			CellType cellType = mGame->getCell(x,y)->getType();

			if (mGame->getCell(x,y)->getEntities().size() > 0) {
				auto topEntity = mGame->getCell(x,y)->getEntities().back();
				auto search = entityInfoMap.find(typeid(*topEntity));

				if (topEntity == mPlayer) {
					cout << '@';
				} else if (search != entityInfoMap.end()){
					cout << search->second.mapIcon;
				} else {
					cout << '?';
				}

			} else if (cellType == CellType::Wall) {
				if (checkIfVerticalWall(x, y)) {
					cout << "|";
				}
				else {
					cout << "-";
				}
			} else if (cellType == CellType::Floor) {
				cout << ".";
			} else if (cellType == CellType::Door) {
				cout << "+";
			} else if (cellType == CellType::Passage) {
				cout << "#";
			} else if (cellType == CellType::Stair) {
				cout << "\\";
			} else {
				cout << " ";
			}
		}
		cout << endl;
	}

	ostringstream raceLine {};

	auto search = entityInfoMap.find(typeid(*mPlayer));
	string playerRace = "Unknown";
	if (search != entityInfoMap.end()) {
		playerRace = search->second.name;
	}

	raceLine << "Race: " << playerRace
		<< " Gold: " << mPlayer->getGold();

	cout << setw(70) << left << raceLine.str()
		<< "Floor: " << mLevel << endl;

	Stats charStats = mPlayer->getStats();

	cout << "HP: " << mPlayer->getHealth() << endl;
	cout << "Atk: " << charStats.attack << endl;
	cout << "Def: " << charStats.defence << endl;
	cout << "Action: " << mMessages.str() << endl;
}

void CLIView::updateView() {
	// This is OS dependent
	system("clear");
	printGrid();
}

void CLIView::turnUpdate() {
	mMessages.str("");
}

void CLIView::notify(DebugMessage & msg) {
	mMessages << "Debug Message: " << msg.message;
}

void CLIView::notify(InfoMessage & msg) {
	mMessages << msg.message << " ";
}

void CLIView::notify(CharacterDeath & msg) {
	if (msg.killed == mPlayer) {
		mMessages << "PC dies. ";
	}
	else {
		mMessages << entityInfoMap.at(typeid(*msg.killed)).name
			<< " dies. ";
	}
}

// Macro to save code
#define getEntityString(FIELD) \
	if (msg.FIELD == mPlayer) { \
		FIELD = "PC"; \
	} else { \
		FIELD = entityInfoMap.at(typeid(*msg.FIELD)).name; \
	} 
// Macro end

//TODO: Add misses
void CLIView::notify(CharacterAttack & msg) {
	string attacker;
	string defender;

	getEntityString(attacker)
	getEntityString(defender)

	if (msg.isMiss) {
		mMessages << attacker << " misses " << defender;
	}
	else {
		mMessages << attacker << " deals " << msg.damage
			<< " damage to " << defender;
	}

	if (msg.defender != mPlayer) {
		mMessages << "(" << msg.defender->getHealth() << "). ";
	}
	else {
		mMessages << ". ";
	}
}

void CLIView::notify(ItemUsed & msg) {
	if (mPlayer == msg.character) {
		mMessages << "PC used a " << 
			entityInfoMap.at(typeid(*msg.item)).name << ". "; 
	} else {
		mMessages << "Enemy used an item??? ";
	}	
}

void CLIView::notify(EntityCreated & msg) {
	//mMessages << "An entity was created. ";
}

void CLIView::notify(EntityRemoved & msg) {
	//mMessages << "An entity was removed. ";
}

void CLIView::notify(GridCreated & msg) {
	mMessages << "Grid created. ";
	mGame = msg.theGame;
}

void CLIView::notify(EntityObserved & msg) {
	if (mPlayer == msg.observer) {
		Position playerPos = mPlayer->getPos();

		entityInfo info = entityInfoMap.at(typeid(*msg.observed));

		string entityName = info.unknownName;

		if (mPlayer->hasKnowledgeOf(msg.observed)) {
			entityName = info.name;
		}

		Direction dir = msg.observed->getPos()
			.calcDirectionGivenPos(playerPos);
		mMessages << "PC sees a " << entityName
			 << " in " << directionStringMap.at(dir) << ". ";
	}
}

void CLIView::notify(ItemPickedUp & msg) {
	if (mPlayer == msg.character) {
		mMessages << "PC picked up " << 
			entityInfoMap.at(typeid(*msg.item)).name << ". "; 
	} else {
		mMessages << "Enemy picked up item??? ";
	}	
}

void CLIView::notify(EntityMoved & msg) {
	if (mPlayer == msg.entity) {
		Position newPos = mPlayer->getPos();
		Direction dir = newPos.calcDirectionGivenPos(msg.oldPos);
		mMessages << "PC moved " << directionStringMap.at(dir) << ". ";
	}
}
