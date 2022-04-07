#BINARY = bin
CODEDIRS = . 
#INCDIRS = . ./include/ # can be list

#CC = gcc
#OPT = -O0
# generate files that encode make rules for the .h dependencies
#DEPFLAGS = -MP -MD
# automatically add the -I onto each include directory
#CFLAGS = -Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
# regular expression replacement
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

#all: $(OBJECTS)

output: $(OBJECTS)
	gcc -pthread $(OBJECTS) -o Hybrid

%.o: %.c
	gcc -Wall -c $^ -lpigpio -lm

clean:
	rm *.o Hybrid

# include the dependencies
-include $(DEPFILES)