#include <memory>
#include "randomAI.h"
#include "../../model/position.h"
#include "../../model/cell.h"
#include "../../model/entity/baseCharacters.h" // includes baseCharacters and all superClasses
#include "../../model/game.h"

using namespace std;

void RandomAI::processTurn(std::shared_ptr<Character> charToMove) {
	Position charPos = charToMove->getPos();
	
	//loop through all cells around character
	//check if should attack
	for (int i = -1 ; i <= 1 ; i++){ for (int j = -1 ; j <= 1 ; j++) { if (i != 0 && j !=0) {
		shared_ptr<Character> checkChar = mGame->getCell(charPos.x+i, charPos.y+j)->getCharacter();
		if (checkChar && mGame->getFactionRelation(charToMove->getFaction(),
							   checkChar->getFaction()) 
					== FactionRelation::hostile) {
			//if hostile, attack!
			charToMove->attack(checkChar);
			return;
		}
	}}}
	
	//if dragon, special logic TODO
	/*
	if (typeid(charToMove) == typeid(Dragon)) {
		for (int i = -1 ; i <= 1 ; i++) { for (int j=-1;j<=1;j++) { if(i!=0&&j!=0) {
			shared_ptr<Character> checkChar = mGame->getCell(charPos.x
		}}}
		return; // dragons never move
	}
	*/

	//else, should move
	vector<Direction> possibleMoves;
	for (int i=-1;i<=1;i++) { for (int j=-1;j<=1;j++) { if (i != 0 && j !=0) {
		Position newPos {charPos.x+i, charPos.y+j};
		if (mGame->getCell(newPos)->canWalkOn()) {
			possibleMoves.emplace_back(newPos.calcDirectionGivenPos(charPos));
		}
	}}}
	mGame->move(charToMove, possibleMoves[rand() % possibleMoves.size()] );
}
