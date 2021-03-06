#ifndef GRID_INIT_RANDOM_GEN_H
#define GRID_INIT_RANDOM_GEN_H

#include "gridInit.h"
#include "../messaging/observer.h"
#include <memory>
#include <fstream>
#include <string>
#include <vector>

class Grid;
class Character;

class GridInitRandomGen : public GridInit {

	std::shared_ptr<Character> mPlayer;
	std::ifstream mFile;
	std::shared_ptr<std::vector<std::weak_ptr<Observer>>> mObservers;

	std::vector<std::vector<std::shared_ptr<Cell>>> mRooms;

	void generateRoom(int roomId, int posx, int posy, std::shared_ptr<Grid>);
	void generateEntities(std::vector<std::vector<std::shared_ptr<Entity>>(*)()>, 
		int, std::shared_ptr<Grid>);

public:
	GridInitRandomGen(std::shared_ptr<Character>, const std::string, 
		std::shared_ptr<std::vector<std::weak_ptr<Observer>>>);
	~GridInitRandomGen();

	virtual std::shared_ptr<Grid> createGrid() override;
	virtual void createEntities(std::shared_ptr<Grid>) override;
};

#endif // GRID_INIT_RANDOM_GEN_H
