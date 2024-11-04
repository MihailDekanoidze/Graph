ifeq ($(origin CC), default)
	CC = g++
endif

CFLAGS ?= -O0 


CFLAGS += -Wall -Wextra

OBJ_DIR    = Apps
SOURCE_DIR = src
EXECUTABLE = proga
INCL_DIR   = include
SUBDIRS    = . SOURCE_DIR

MAKEFLAGS += --no-print-directory

override CFLAGS += -I./include


#ALL_CPP = main.cpp source/Triangle.cpp

#.PHONY: all Triangle_Proc clean run $(OBJECTS) test
#OBJECTS := $(notdir $(patsubst %.cpp, %.o, $(ALL_CPP)))
#SOURCES = source/%.o

SOURCES := main.o src/graph1.o
OBJECTS := $(addprefix $(OBJ_DIR)/, $(SOURCES: %.cpp=%.o))
DEPS    := $(OBJECTS:%.cpp=%.d)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $^ -o $@ $(LDFLAGS)    

$(OBJECTS):$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(CFLAGS) 

#Apps/main.o: main.cpp

#	$(CC) $^ -c -o $@ $(CFLAGS)
#
#Apps/Triangle.o: source/Triangle.cpp
#	$(CC) $^ -c -o $@ $(CFLAGS)

clean:
	rm -rf *.o
	rm $(EXECUTABLE)

run:
	./proga

NODEPS = clean

