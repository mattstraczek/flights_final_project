#Executable names:
EXE = out
TEST = test

#Add all object files needed for compiling:
EXE_OBJ = main.o 
OBJS = main.o airport.o routes.o parsing.o graph.o

#Generated files

#Use the cs225 makefile template:
include cs225/make/cs225.mk