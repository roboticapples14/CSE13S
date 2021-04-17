Natalie Valett
nvalett
CSE13S Assignment 2: A Small Numerical Library


This project is meant to replicate the functionality of a subset of the <math.h> library. It includes functions for arcSin, arcCos, arcTan, and Log.
mathlib.c simply defines these functions, and mathlib-test.c is a test harness which runs tests of the functions specified by user input.

TO BUILD:
type "make" in the unix terminal when open to the asgn2 directory and press enter. This should run the commands in Makefile which format and compile all necessary files.

TO RUN:
After building the project, there should be 2 new executables in the directory, mathlib and mathlib-test. To run the test harness you enter "./mathlib-test -<options>" in the terminal, where <options> correspond to the functions you want to test (-s = arcsin, -c = arccos, -t = arctan, -l = log, -a = all)
The program will then run the test harness for all specified functions. The output contains the results and comparison between both the personally-defined math functions and their counterparts from the math.h library.
