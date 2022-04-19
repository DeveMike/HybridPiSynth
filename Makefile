CC = gcc
OUTPUT = Hybrid
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

output: $(OBJECTS)
	$(CC) $(OBJECTS) -pthread -lm -lpigpio -o $(OUTPUT)

$(OBJECTS): $(SOURCES)
	$(CC) -Wall -c $?

run:
	make
	@echo;echo;echo;echo
	sudo ./$(OUTPUT)

clean:
	rm *.o $(OUTPUT)