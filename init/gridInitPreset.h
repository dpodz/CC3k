#ifndef GRID_INIT_PRESET_H
#define GRID_INIT_PRESET_H

#include "gridInit.h"
#include "../state/grid.h"
#include "../state/entity/character.h"
#include <memory>
#include <fstream>
#include <string>

class GridInitPreset : public GridInit {

	std::weak_ptr<Character> mPlayer;
	std::ifstream mFile;

public:
	GridInitPreset(std::shared_ptr<Character>, const std::String);
	~GridInitPreset();

	virtual Grid createGrid() override;
	virtual void createEntities(std::shared_ptr<Grid>) override;
};

#endif // GRID_INIT_PRESET_H
