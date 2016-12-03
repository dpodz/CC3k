#include <memory>
#include "randomAI.h"
#include "../../model/position.h"
#include "../../model/cell.h"
#include "../../model/entity/baseCharacters.h" // includes baseCharacters and all superClasses
#include "../../model/game.h"

using namespace std;

RandomAI::RandomAI(shared_ptr<Game> theGame): CharacterAI{theGame} { }
RandomAI::~RandomAI() { }

void RandomAI::processTurn(std::shared_ptr<Character> charToMove) {
	Position charPos = charToMove->getPos();
	
	//loop through all cells around character
	//check if should attack
	for (int i = -1 ; i <= 1 ; i++){ 
		for (int j = -1 ; j <= 1 ; j++) { 
			if (i != 0 || j !=0) {
				try {
					auto checkChar = mGame->getCell(charPos.x+i, charPos.y+j)->getCharacter();
					if (mGame->getFactionRelation(charToMove->getFaction(), checkChar->getFaction()) == FactionRelation::hostile) {
						//if hostile, attack!
						charToMove->attack(checkChar);
						return;
					}
				} catch (...) { }
			}
		}
	}
	
	//if dragon, special logic
	if (typeid(*charToMove) == typeid(Dragon)) {
		if (!static_pointer_cast<Dragon>(charToMove)->getHoard()) { 
			return; // If no hoard
		} 
		Position hoardPos = static_pointer_cast<Dragon>(charToMove)->getHoard()->getPos();
		for (int i = -1 ; i <= 1 ; i++) { 
			for (int j = -1; j <= 1; j++) { 
				if(i !=0 || j !=0 ) {
					try {
						auto checkChar = mGame->getCell(hoardPos.x+i, hoardPos.y+j)->getCharacter();
						if (mGame->getFactionRelation(charToMove->getFaction(), checkChar->getFaction()) == FactionRelation::hostile) {
							// If hostile, attack
							charToMove->attack(checkChar);
							return;
						}
					} catch (...) { }
				}
			}	
		}
		return; // dragons never move
	}

	//else, should move
	vector<Direction> possibleMoves;
	for (int i = -1; i <= 1; i++) { 
		for (int j = -1; j <= 1; j++) { 
			if (i != 0 || j !=0) { 
				Position newPos {charPos.x+i, charPos.y+j};
				shared_ptr<Cell> newCell = mGame->getCell(newPos);
				//valid move, don't move into doors, and no entities (potions, gold)
				if (newCell->isValidMove() &&
					newCell->getType() != CellType::Door &&
					newCell->getEntities().size() == 0) {
					possibleMoves.emplace_back(newPos.calcDirectionGivenPos(charPos));
				}
			}
		}
	}
	
	if (!possibleMoves.empty()) {
		mGame->move(charToMove, possibleMoves[rand() % possibleMoves.size()] );
	}
}

void RandomAI::notify(CharacterAttack & msg) {
	mGame->setFactionRelation(msg.defender->getFaction(), 
		msg.attacker->getFaction(), FactionRelation::hostile);

	if (msg.defender->getHealth() - msg.damage <= 0) {
		if (typeid(*msg.defender) != typeid(Dragon)
			&& typeid(*msg.defender) != typeid(Merchant)
			&& typeid(*msg.defender) != typeid(Human)) {
			if (rand() % 2 == 0) {
				msg.attacker->setGold(msg.attacker->getGold() + 1);
			}
			else {
				msg.attacker->setGold(msg.attacker->getGold() + 2);
			}
		}
	}
}

