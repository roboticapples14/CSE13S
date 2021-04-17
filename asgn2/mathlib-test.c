#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

int main(int argc, char **argv) {
    int opt = 0;
    int arcsin = 0;
    int arccos = 0;
    int arctan = 0;
    int logorithm = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            arcsin = 1;
            arccos = 1;
            arctan = 1;
            logorithm = 1;
            break;
        case 's': arcsin = 1; break;
        case 'c': arccos = 1; break;
        case 't': arctan = 1; break;
        case 'l': logorithm = 1; break;
        default:
            printf("Invalid input. Correct usage is as follows:\nEnter:\n\ts for arcsin\n\tc for "
                   "cossin\n\tt for arctan\n\tl for log\n\ta for all.\n");
            return 1;
        }
    }
    // Executes functions
    if (arcsin == 1) {
        printf("x\t\tarcSin\t\tLibrary\t\tDifference\n");
        printf("-\t\t------\t\t-------\t\t----------\n");

        // range = [-1, 1), step = 0.1
        for (double i = -1.0; i < 1.0; i += 0.1) {
            printf(
                "%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcSin(i), asin(i), arcSin(i) - asin(i));
        }
    }
    if (arccos == 1) {
        printf("x\t\tarcCos\t\tLibrary\t\tDifference\n");
        printf("-\t\t------\t\t-------\t\t----------\n");
        // range = [-1, 1), step = 0.1
        for (double i = -1.0; i < 1.0; i += 0.1) {
            printf(
                "%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcCos(i), acos(i), arcCos(i) - acos(i));
        }
    }
    if (arctan == 1) {
        printf("x\t\tarcTan\t\tLibrary\t\tDifference\n");
        printf("-\t\t------\t\t-------\t\t----------\n");
        // range = [1, 10), step = 0.1
        for (double i = 1.0; i < 10.0; i += 0.1) {
            // credit to Wednesday 10am section on 4/14 for number formatting
            printf(
                "%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcTan(i), atan(i), arcTan(i) - atan(i));
        }
    }
    if (logorithm == 1) {
        printf("x\t\tLog\t\tLibrary\t\tDifference\n");
        printf("-\t\t------\t\t-------\t\t----------\n");
        // range = [1, 10), step = 0.1
        for (double i = 1.0; i < 10.0; i += 0.1) {
            // credit to Wednesday 10am section on 4/14 for number formatting
            printf("%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
        }
    }
}
