output: Main.o PWMout.o
	gcc Main.o PWMout.o -o Hybrid

Main.o: Main.c
	gcc -Wall -c Main.c -l pigpio -lpthread -lm

PWMout.o: PWMout.c
	gcc -Wall -c PWMout.c -l pigpio -lpthread -lm

clean:
	rm *.o Hybrid
