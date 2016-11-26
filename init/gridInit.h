#ifndef GRID_INIT_H
#define GRID_INIT_H

#include "../state/grid.h"
#include <memory>

class GridInit {

public:
	GridInit();
	~GridInit(); 

	virtual Grid createGrid() = 0;
	virtual void createEntities(std::shared_ptr<Grid>) = 0;
};

#endif // GRID_INIT_H
