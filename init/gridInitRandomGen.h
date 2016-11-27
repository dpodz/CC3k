#ifndef GRID_INIT_RANDOM_GEN_H
#define GRID_INIT_RANDOM_GEN_H

#include "gridInit.h"
#include <memory>
#include <fstream>
#include <string>

class Grid;
class Character;

class GridInitRandomGen : public GridInit {

	std::weak_ptr<Character> mPlayer;
	std::ifstream mFile;

public:
	GridInitRandomGen(std::shared_ptr<Character>, const std::String);
	~GridInitRandomGen();

	virtual std::unique_ptr<Grid> createGrid() override;
	virtual void createEntities(std::shared_ptr<Grid>) override;
};

#endif // GRID_INIT_RANDOM_GEN_H
