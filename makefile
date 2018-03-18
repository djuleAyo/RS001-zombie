SRC= $(shell find ./ -name *.cpp | grep src/)
OBJ= $(shell echo $(SRC:.cpp=.o) | sed  s/src/build\\/production/g)
DEBUG_OBJ= $(shell echo $(SRC:.cpp=.o) | sed  s/src/build\\/debug/g)

INC= -Iinc
LIB= -Llib

LFLAGS=
DFLAGS= -Wall -Wextra -pg -g
PFLAGS = -O3

#passing these link flags in calls that make bins.
#These and -D__OLD_GL should be toggled together
#Both are not merged since from some strange reason linking fails
#if glut link flags are passed before file names
#Usage: toggle $(OLD_GL) in calls that make bins and -D__OLD_GL in
#compiler definition
OLD_GL= -lGL -lGLU -lglut


C= g++ -std=c++17 $(INC) $(LFLAGS) -D__OLD_GL

################################################################################
# "public" use these commands to manage the project
################################################################################

#by default make debug variant and run it
drun: debug
	./bin/$^

debug: $(DEBUG_OBJ)
	$(C) $(DFLAGS) -obin/$@ $^ $(OLD_GL)

minecraftCpp: $(OBJ)
	$(C) -obin/$@ $^ $(OLD_GL)

run: minecraftCpp
	./bin/$^



################################################################################
# "private" - public commands depend on these.
################################################################################
build/debug/%.o: src/%.cpp
	$(C) $(DFLAGS) $< -c -o$@


build/production/%.o: src/%.cpp
	$(C) $(PFLAGS) $< -c -o$@


.PHONY: clean

clean:
	rm build/debug/* build/production/* bin/* *.out 
