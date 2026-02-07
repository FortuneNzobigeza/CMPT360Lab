# Student Name: Fortune Nzobigeza
# Student ID: 3131442
# Submission Date: Feb 21st 2026
# File Name: Makefile

CC:= gcc-13 
CFLAGS:= -std=c11 -Wall -Wextra -pedantic -O2 -g 

#Valgrind 
VALGRIND?=valgrind 
VGFLAGS?= --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=all --error-exitcode=1 

.PHONY: all clean check valgrind vg 

all: sched

sched:sched.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

sched.o:sched.c 
	$(CC) $(CFLAGS) -c $< 


#test cases
check: sched
	
#Check Memory leaks
valgrind: sched 
	@$(VALGRIND)$(VGFLAGS) ./sched < input.txt

vg: valgrind 

clean: 
	@rm -f sched sched.o