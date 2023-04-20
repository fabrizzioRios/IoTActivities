CC = gcc
CFLAGS = -Wall -Werror -g
OUTPUT = Server.out
SOURCES = Server.c com.c mqtt_frames.c
LIBS = -pthread com.h mqtt_frames.h
# $(CFLAGS)
all:
	$(CC) $(LIBS) $(SOURCES) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT) 
fresh: clean all
