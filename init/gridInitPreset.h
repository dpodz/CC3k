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
	vector<vector<std::shared_ptr<Cell>>> mRooms;
	void generateRoom(int roomId, int posx, int posy);
	std::shared_ptr<Entity> getRandomEntity(vector<std::shared_ptr<Entity>>);
public:
	GridInitPreset(std::shared_ptr<Character>, const std::string);
	~GridInitPreset();

	virtual std::shared_ptr<Grid> createGrid() override;
	virtual void createEntities(std::shared_ptr<Grid>) override;
};

#endif // GRID_INIT_PRESET_H
