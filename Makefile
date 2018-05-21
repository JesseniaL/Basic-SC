# Jessenia Lopez
# Makefile for shell_project
#
# This Makefile will:
# Compile shell_functions.c and shell_functions.h into an object file shell_functions.o
# Compile shell_project.c into shell.o
# Link and generate the executable file shell_project

shell: shell_project.o shell_functions.o
	gcc -o shell shell_project.o shell_functions.o

shell_project.o: shell_project.c shell_functions.h
shell_functions.o: shell_functions.c shell_functions.h