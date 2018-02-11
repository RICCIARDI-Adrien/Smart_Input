CC = gcc
CCFLAGS = -W -Wall

PATH_INCLUDES = Includes
PATH_SOURCES = Sources

BINARY = smart-input
INCLUDES = -I$(PATH_INCLUDES)
SOURCES = $(shell find $(PATH_SOURCES) -name "*.c")

# Build in release mode by default when typing "make"
release: CCFLAGS += -O2 -DNDEBUG
release: all

debug: CCFLAGS += -O0 -g
debug: all

all:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) -o $(BINARY)

clean:
	rm -r $(BINARY)
