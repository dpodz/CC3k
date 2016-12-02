#include <iostream>
#include "messaging/messages.h"
#include "messaging/observer.h"
#include "messaging/subject.h"
#include "view/CLIView.h"
#include "controller/CLIController.h"
#include <memory>

using namespace std;

int main() {
 	
	string mapString = "test.map";

	auto controller = make_shared<CLIController>(mapString, true);

	controller->playGame();

	return 0;
}
