# Student Name: Fortune Nzobigeza
# Student ID: 3131442
# Submission Date: January 24th 2026
# File Name: Makefile

CC:= gcc-13 
CFLAGS:= -std=c11 -Wall -Wextra -pedantic -O2 -g 

#Valgrind 
VALGRIND?=valgrind 
VGFLAGS?= --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=all --error-exitcode=1 

.PHONY: all clean check valgrind vg 

all: userclean

userclean:userclean.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

userclean.o:userclean.c 
	$(CC) $(CFLAGS) -c $< 


check: userclean
	@echo 'Bob123' | ./userclean 
	@echo 'a!' | ./userclean 
	@echo 'Admin 42' | ./userclean 
	@echo 'root user' | ./userclean 
	@echo 'ABCDEFGHI' | ./userclean
	@echo 'test' | ./userclean 
	@echo '_99' | ./userclean
	@echo 'admin' | ./userclean
	@echo 'root' | ./userclean
	@echo 'root^' | ./userclean
	@echo 'a)d]m]]]i.n' | ./userclean
	@echo '' | ./userclean
	
#Run sample input under Valgrind; fails build on leaks/errors 
valgrind: userclean 
	@$(VALGRIND)$(VGFLAGS) ./userclean < input.txt

vg: valgrind 

clean: 
	@rm -f userclean userclean.o