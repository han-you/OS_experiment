CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp disk_emu.c sfs_api.c sfs_util.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sfs

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
