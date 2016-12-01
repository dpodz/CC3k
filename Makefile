CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -g
EXEC = cc3k
OBJECTS = \
main.o messaging/messages.o messaging/subject.o messaging/observer.o \
model/grid.o model/game.o model/cell.o controller/controller.o \
controller/CLIController.o view/view.o view/CLIView.o \
controller/ai/randomAI.o controller/ai/characterAI.o\
init/gridInit.o init/gridInitRandomGen.o init/gridInitPreset.o model/entity/entity.o \
model/entity/character.o model/entity/baseCharacters.o model/entity/item.o \
model/entity/potion.o model/entity/basePotions.o model/entity/stats.o \
model/entity/additiveModifier.o model/entity/modifier.o \
model/entity/treasure.o model/entity/baseTreasure.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
