#ifndef GAME_H
#define GAME_H

#include "faction.h"
#include <memory>
#include <map>
#include <utility>

class Grid;
class GridInit;
class Cell;

enum FactionRelation {
	hostile,
	neutral,
	friendly
};

class Game {

	std::unique_ptr<Grid> mGrid;
	std::shared_ptr<GridInit> mGridInit;
	std::map<std::pair<FactionId, FactionId>, FactionRelation> mFactionRelation;

public:
	Game();
	~Game();
	
	void turnUpdate();
	GridSize getGridSize() const;
	std::shared_ptr<Cell> getCell(int, int) const;

	void setGridGen(std::shared_ptr<GridInit>);
	void generateNewGrid();
	void createNewEntities();

	void setFactionRelation(FactionId, FactionId, FactionRelation);
	FactionRelation getFactionRelation(FactionId, FactionId) const;
};

#endif // GAME_H
