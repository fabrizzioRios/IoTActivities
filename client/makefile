CC = gcc
CFLAGS = -Wall -Werror
OUTPUT = client.out
SOURCES = client.c mqtt_frames.c
LIBS = -pthread mqtt_frames.h

all:
	$(CC)  $(LIBS) $(SOURCES) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT) 
fresh: clean all
