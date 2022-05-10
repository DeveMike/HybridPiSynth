OUTPUT = Hybrid.out

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Wshadow -Wundef -Wformat=2 -Wno-float-conversion
EXTRA_CFLAGS = -O2
LFLAGS = -pthread -lm -lpigpio

output: $(OBJECTS)
	$(CC) $? $(LFLAGS) -o $(OUTPUT)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $?

debug:
	make EXTRA_CFLAGS="-g3"
	sudo gdb ./$(OUTPUT)

run:
	make
	@echo;echo;echo
	@sudo ./$(OUTPUT)

clean:
	rm *.o $(OUTPUT) $(SRCOBJS) $(TESTOBJS)
