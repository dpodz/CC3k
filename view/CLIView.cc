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
};

const map<type_index, entityInfo> entityInfoMap {
	{typeid(Human), {'H', "Human"}},
	{typeid(Dwarf), {'W', "Dwarf"}},
	{typeid(Elf), {'E', "Elf"}},
	{typeid(Orc), {'O', "Orc"}},
	{typeid(Merchant), {'M', "Merchant"}},
	{typeid(Dragon), {'D', "Dragon"}},
	{typeid(Halfling),{'L', "Halfling"}},
	{typeid(Potion), {'P', "Potion"}},
	{typeid(RestoreHealth), {'P', "Restore Health"}},
	{typeid(BoostAtk), {'P', "Boost Attack"}},
	{typeid(BoostDef), {'P', "Boost Defence"}},
	{typeid(PoisonHealth), {'P', "Poison Health"}},
	{typeid(WoundAtk), {'P', "Wound Attack"}},
	{typeid(WoundDef), {'P', "Wound Defence"}},
	{typeid(Treasure), {'G', "Treasure"}},
	{typeid(SmallGold), {'G', "Small Gold"}},
	{typeid(NormalGold), {'G', "Normal Gold"}},
	{typeid(MerchantHoard), {'G', "Merchant Hoard"}},
	{typeid(DragonHoard), {'G', "Dragon Hoard"}}
};

CLIView::CLIView(shared_ptr<Character> player, shared_ptr<Game> game):
	mPlayer {player}, mGame {game}, mMessages {} {}

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

	// TODO: Use grid size
	for (int y = 0 ; y < 25 ; ++y) {
		for (int x = 0 ; x < 79 ; ++x) {
			CellType cellType = mGame->getCell(x,y)->getType();

			if (mGame->getCell(x,y)->getEntities().size() > 0) {
				// NOTE: May need to change this to be last item
				auto topEntity = mGame->getCell(x,y)->getEntities()[0];
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

	raceLine << "Race: " << typeid(*mPlayer).name()
		<< " Gold: " << mPlayer->getGold();

	cout << setw(70) << left << raceLine.str()
		<< "Floor: ???" << endl;

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

void CLIView::notify(DebugMessage & dm) {
	cout << "Debug Message: " << dm.message << endl;
}

void CLIView::notify(CharacterDeath & cd) {
	string killerName;
	string killedName;
	
	if (dynamic_pointer_cast<Shade>(cd.killer)) { killerName = "Shade"; } 
	else { killerName = "Not a Shade"; }
	
	if (dynamic_pointer_cast<Shade>(cd.killed)) { killedName = "Shade"; }
	else { killerName = "Not a Shade"; }
	
	mMessages << killerName << " killed " << killedName << ". ";
	//updateView(vector<Position>{cd.killer->getPos, cd.killed->getPos});
}

//TODO
void CLIView::notify(CharacterAttack & ca) {
	mMessages << "A character attacked another character for " << ca.damage << " damage! ";
}

//TODO
void CLIView::notify(ItemUsed & iu) {
	mMessages << "A character used an item. ";
}

//TODO
void CLIView::notify(EntityCreated & ec) {
	mMessages << "An entity was created. ";
}

//TODO
void CLIView::notify(EntityRemoved & er) {
	mMessages << "An entity was removed. ";
}

//TODO
void CLIView::notify(GridCreated & mc) {
	mMessages << "Grid created. ";
	mGame = mc.theGame;
}

//TODO
void CLIView::notify(EntityObserved & eo) {
	mMessages << "An entity observed an entity. ";
}

//TODO
void CLIView::notify(ItemPickedUp & ipu) {
	mMessages << "An item was picked up. ";
}

//TODO
void CLIView::notify(EntityMoved & cm) {
	mMessages << "An entity moved. ";
}
