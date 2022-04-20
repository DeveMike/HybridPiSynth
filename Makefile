CC = gcc
OUTPUT = Hybrid

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Wshadow -Wundef -Wno-unused-parameter -Wformat=2 -Wno-float-conversion
EXTRA_CFLAGS = -O2
LFLAGS = -pthread -lm -lpigpio

output: $(OBJECTS)
	$(CC) $? $(LFLAGS) -o $(OUTPUT)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $?

debug:
	EXTRA_CFLAGS="-g3" make
	sudo gdb ./$(OUTPUT)

run:
	make
	@echo;echo;echo
	@sudo ./$(OUTPUT)

clean:
	rm *.o $(OUTPUT)