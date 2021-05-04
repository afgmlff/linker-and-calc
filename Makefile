CC = g++
RMDIR = rm -rf
RM = rm -f

RUN = ./

DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d

DIRECTIVES = -std=c++11 -c -I $(HEADER_PATH) -g

LIBS = -lm

HEADER_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

EXEC = montador

# if is Windows_NT on XP, 2000, 7, Vista, 10...
ifeq ($(OS),Windows_NT) 

RMDIR = rd /s /q
RM = del

RUN =

SDL_PATH =

DIRECTIVES += -I $(SDL_PATH)\include\SDL2

LIBS = -lm

EXEC := $(EXEC).exe

else
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
endif
endif

all: $(EXEC) simulador ligador

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp

ifeq ($(OS), Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif

	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)

simulador: src/simulador/mainS.cpp
	g++ -std=c++11 -o simulador src/simulador/mainS.cpp src/simulador/simulador.cpp 


ligador: src/ligador/mainL.cpp
	g++ -std=c++11 -o ligador src/ligador/mainL.cpp src/ligador/ligador.cpp 

print-% : ; @echo $* = $($*)

debug: DIRECTIVES += -ggdb -O0 -DDEBUG
debug: all

dev: debug run

gdb: RUN := gdb $(RUN)
gdb: dev

release: DIRECTIVES += -Ofast -mtune=native
release: all

run:
	$(RUN)$(EXEC)

clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)
	$(RM) $(EXEC)
	$(RM) $(EXEC_S)

.PRECIOUS: $(DEP_PATH)/%.D

.PHONY: debug clean release

-include $(DEP_FILES)