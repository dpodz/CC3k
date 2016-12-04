#include <iostream>
#include "view/CLIView.h"
#include "controller/CLIController.h"
#include <memory>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

	string mapString = "default.map";
	bool customMap = false;

	if (argc > 3) {
		cerr << "Invalid number of arguments entered" << endl;
		return 1;
	}

	if (argc > 1) {
		if (string(argv[1]) == "--custom") {
			if (argc < 3) {
				cerr << "Map file not specified" << endl;
				return 1;
			}
			mapString = argv[2];
			customMap = true;
		}
	}

	auto controller = make_shared<CLIController>(mapString, customMap);

	controller->playGame();

	return 0;
}
