#include <iostream>
#include "messaging/messages.h"
#include "messaging/observer.h"
#include "messaging/subject.h"
#include "view/CLIView.h"
#include "controller/CLIController.h"
#include "model/game.h"
#include <memory>

using namespace std;

int main() {
 	
	string mapString = "test.map";

	auto game = make_shared<Game>();

	auto controller = make_shared<CLIController>(game, mapString, true);

	controller->playGame();

	return 0;
}
