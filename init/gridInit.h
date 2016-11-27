#ifndef GRID_INIT_H
#define GRID_INIT_H

<<<<<<< HEAD
#include "../model/grid.h"
=======
>>>>>>> 993b3a25628111809407d78b7a2841444745761a
#include <memory>

class Grid;

class GridInit {

public:
	GridInit();
	~GridInit(); 

	virtual std::unique_ptr<Grid> createGrid() = 0;
	virtual void createEntities(std::shared_ptr<Grid>) = 0;
};

#endif // GRID_INIT_H
