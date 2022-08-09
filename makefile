#makefile

lab06: lab06.o ghcontrol.o
	g++ -g -o lab06 lab06.o ghcontrol.o
lab06.o: lab06.c ghcontrol.h
	g++ -g -c lab06.c

ghcontrol.o: ghcontrol.c ghcontrol.h
	g++ -g -c ghcontrol.c
clean:
	touch *
	rm *.o









