COMPILER = g++

COMPILER_FLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror -Wshadow -O2 -g

HEADER_DIRS =
LIBRARY_DIRS =
LIBS =

SOURCES = main.cpp
OUTPUT_FILE = main

all: $(OBJS)
	$(COMPILER) $(SOURCES) $(HEADER_DIRS) $(LIBRARY_DIRS) $(COMPILER_FLAGS) $(LIBS) -o $(OUTPUT_FILE)
