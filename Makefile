# AED, last modified abl 2019.04.02
#
# To compile prog:
#    make
# To run tests:
#    make t
#
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -Wall -std=c99 -O3

#   Sources
SOURCES = roap_main.c 

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS_A = roap_main.o 


roap: $(OBJECTS_A)
	$(CC) $(CFLAGS) -o roap $(OBJECTS_A)

roapsolver_main.o: roap_main.c roap_lib.h

clean:
	rm -f *.o *.~ words *.gch


FILES = $(shell ls test/*.camp0)

VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./roap $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./roap $${F} ; done;


tt:
	for F in ${FILES}; do  time ./roap $${F} ; done;

