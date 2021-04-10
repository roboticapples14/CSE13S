Natalie Valett
nvalett
CSE13S Assignment 1: Left, Right and Center

This program simulates a game of LRC (Left, Right and Center) in which the user inputs the number of players and a starting seed, and the program runs until a winner is chosen. Taking turns in a circle, each player rolls the amount of dice equivelent to the amount of money they hold (or just 3 if they have more than $3), and depending on what they roll they either need to give a dollar to the person on their right, left, or the pot, or they may pass if they roll a pass. This continues until only 1 player has money, at which point the game ends and that player wins.

TO BUILD:
type "make" in the unix terminal when open to the asgn1 directory and press enter. This should run the commands in Makefile which format and compile lrc.c.

TO RUN:
After building the project, there should be a new executible called lrc in the directory. To run it you type "./lrc" in the terminal and hit enter.
The program will prompt you for 2 integer inputs, each time enter your number and press enter.
