#Makefile

#.RECIPEPREFIX +=

# Specify compiler
CC = g++
# Compiler flags, if you want debug info, add -g
CCFLAGS = -std=c++11 -g3 -Wall -c
CFLAGS = -g3 -c

# object files
OBJS = pageTableLevel.o tracereader.o main.o log.o

# Program name
PROGRAM = pagetrace

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)

main.o : main.cpp 
	$(CC) $(CCFLAGS) main.cpp

pageTableLevel.o : pageTableLevel.cpp pageTableLevel.hpp
	$(CC) $(CCFLAGS) pageTableLevel.cpp

tracereader.o : tracereader.cpp tracereader.hpp
	$(CC) $(CFLAGS) tracereader.cpp

log.o : log.cpp log.hpp
	$(CC) $(CFLAGS) log.cpp

# Once things work, people frequently delete their object files.
# If you use "make clean", this will do it for you.
# As we use gnuemacs which leaves auto save files termintating
# with ~, we will delete those as well.
clean :
	rm -rf $(OBJS) *~ $(PROGRAM)