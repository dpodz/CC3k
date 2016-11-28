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

class CLIView : public View {

	std::weak_ptr<Character> mPlayer;
	std::shared_ptr<Game> mGame;
	
	void printGrid();

public:

	CLIView(std::shared_ptr<Character>, std::shared_ptr<Game>);
	~CLIView();
	
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
};

#endif // CLI_VIEW_H
