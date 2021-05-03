Natalie Valett
nvalett
CSE13S Assignment 4: The Circumnavigations of Denver Long


This lab’s objective is to find the shortest path that can be taken to visit each city given in the input exactly once. The program will first read in the input of city names and take in their coordinates and distances from each other. Then we’ll perform a recursive depth-first search which will calculate all possible paths between all the vertices, and save only the shortest path. The program will then print out the fastest path found.

TO RUN:
After building the project by entering 'make' in the console, there should be a new executable in the directory called tsp. To run the program enter "./tsp [options]" in the terminal, where [options] include:
	-h: Prints out a help message for program usage
	-v: Enables verbose printing. If enabled, the program prints out all Hamiltonian paths found and the number of recursive calls
	-u: Specifies the graph to be undirected.
	-i infile: Specify the input file path containing the cities and edges of a graph. If not specified, defaults to stdin.
	-o outfile: Specify the output file path to print to. If not specified, defaults to stdout.
