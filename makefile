#David Rasper
#Z1642905
#Assignment 3

Assign4: Assign4.o
	g++ -Wall -o Assign4 Assign4.o
#
Assign4.o: Assign4.cc Process.h
	g++ -Wall -c Assign4.cc
