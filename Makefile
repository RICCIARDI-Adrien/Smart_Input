CC = gcc
CCFLAGS = -W -Wall

PATH_INCLUDES = Includes
PATH_SOURCES = Sources

BINARY = smart-input
INCLUDES = -I$(PATH_INCLUDES)
SOURCES = $(shell find $(PATH_SOURCES) -name "*.c")

all:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) -o $(BINARY)

clean:
	rm -r $(BINARY)
