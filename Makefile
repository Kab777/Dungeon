CXX = g++
CXXFLAGS = -Wall -MMD -Wno-reorder
EXEC = cc3k
OBJECTS = main.o Boost_Atk.o dragon_hoard.o halfling.o normal_gold.o Restore_Health.o Wound_Atk.o Boost_Def.o dwarf.o human.o orcs.o small_gold.o Wound_Def.o character.o elf.o item.o player.o textdisplay.o controller.o enemy.o merchant.o Poison_Health.o Treasure.o dragon.o floor.o merchant_hoard.o potion.o unit.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
