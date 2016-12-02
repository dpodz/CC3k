#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include "view.h"
#include "../model/entity/character.h"
#include "../model/entity/baseCharacters.h"
#include "../model/entity/entity.h"
#include "../model/game.h"
#include "../model/grid.h"
#include "../model/cell.h"
#include <memory>
#include <sstream>

class CLIView : public View {

	std::shared_ptr<Character> mPlayer;
	std::shared_ptr<Game> mGame;
	std::ostringstream mMessages;
	int mLevel;
	
	bool checkIfVerticalWall(int, int);
	void printGrid();

public:

	CLIView(std::shared_ptr<Character>, std::shared_ptr<Game>);
	~CLIView();

	void updateView() override;
	void turnUpdate() override;
	
	virtual void notify(CharacterDeath &) override;
	virtual void notify(CharacterAttack &) override;
	virtual void notify(EntityMoved &) override;
	virtual void notify(EntityCreated &) override;
	virtual void notify(EntityRemoved &) override;
	virtual void notify(EntityObserved &) override;
	virtual void notify(ItemUsed &) override;
	virtual void notify(ItemPickedUp &) override;
	virtual void notify(GridCreated &) override;
	virtual void notify(DebugMessage &) override;
	virtual void notify(InfoMessage &) override;
};

#endif // CLI_VIEW_H
