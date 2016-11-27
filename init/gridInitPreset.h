#ifndef GRID_INIT_PRESET_H
#define GRID_INIT_PRESET_H

#include "gridInit.h"
<<<<<<< HEAD
#include "../model/grid.h"
#include "../model/entity/character.h"
=======
>>>>>>> 993b3a25628111809407d78b7a2841444745761a
#include <memory>
#include <fstream>
#include <string>

class Character;
class Grid;

class GridInitPreset : public GridInit {

	std::weak_ptr<Character> mPlayer;
	std::ifstream mFile;

public:
	GridInitPreset(std::shared_ptr<Character>, const std::string);
	~GridInitPreset();

	virtual std::unique_ptr<Grid> createGrid() override;
	virtual void createEntities(std::shared_ptr<Grid>) override;
};

#endif // GRID_INIT_PRESET_H
