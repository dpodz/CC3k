#include "gridInitPreset.h"

GridInitPreset::GridInitPreset(std::shared_ptr<Character> player, const std::String fileName): 
	mPlayer{player}, mFile(fileName, std::ifstream::in) {}

GridInitPreset::~GridInitPreset() {}

std::unique_ptr<Grid> GridInitPreset::createGrid() {
	if (!mFile.isOpen()){
		throw "cannot open file";
	}
	std::string line;
	vector<
	while (getline(mFile, line)) {
		
