#ifndef GRID_INIT_PRESET_H
#define GRID_INIT_PRESET_H

#include "gridInit.h"
#include "../model/grid.h"
#include "../model/entity/entity.h"
#include "../model/entity/character.h"
#include "../model/entity/baseCharacters.h"
#include <memory>
#include <fstream>
#include <string>
#include <vector>

class Character;
class Grid;

class GridInitPreset : public GridInit {
	std::shared_ptr<Character> mPlayer;
	std::ifstream mFile;
	std::shared_ptr<std::vector<std::shared_ptr<Observer>>> mObservers;

public:
	GridInitPreset(std::shared_ptr<Character>, const std::string, 
		std::shared_ptr<std::vector<std::shared_ptr<Observer>>>);
	~GridInitPreset();

	std::shared_ptr<Grid> createGrid() override;
	void createEntities(std::shared_ptr<Grid>) override;
};

#endif // GRID_INIT_PRESET_H
