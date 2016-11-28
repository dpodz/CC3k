#ifndef GRID_INIT_H
#define GRID_INIT_H

#include "../model/grid.h"
#include <memory>

class Grid;

class GridInit {

public:
	GridInit();
	~GridInit(); 

	virtual std::shared_ptr<Grid> createGrid() = 0;
	virtual void createEntities(std::shared_ptr<Grid>) = 0;
};

#endif // GRID_INIT_H
