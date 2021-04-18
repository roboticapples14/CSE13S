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
            printf("Program usage: ./mathlib-test -[asctl]\n");
            printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
            printf("  -s   Runs arcsin tests\n");
            printf("  -c   Runs arccos tests\n");
            printf("  -t   Runs arctan tests\n");
            printf("  -l   Runs log tests\n");
            return 1;
        }
    }
    if (arcsin == 0 && arccos == 0 && arctan == 0 && logorithm == 0) {
        printf("Program usage: ./mathlib-test -[asctl]\n");
        printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
        printf("  -s   Runs arcsin tests\n");
        printf("  -c   Runs arccos tests\n");
        printf("  -t   Runs arctan tests\n");
        printf("  -l   Runs log tests\n");
    }
    // Executes functions
    if (arcsin == 1) {
        printf(" x            arcSin           Library        Difference\n");
        printf(" -            ------           -------        ----------\n");

        // range = [-1, 1), step = 0.1
        for (double i = -1.0; i < 1.0; i += 0.1) {
            printf(
                "%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcSin(i), asin(i), arcSin(i) - asin(i));
        }
    }
    if (arccos == 1) {
        printf(" x            arcCos           Library        Difference\n");
        printf(" -            ------           -------        ----------\n");
        // range = [-1, 1), step = 0.1
        for (double i = -1.0; i < 1.0; i += 0.1) {
            printf(
                "%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcCos(i), acos(i), arcCos(i) - acos(i));
        }
    }
    if (arctan == 1) {
        printf(" x            arcTan           Library        Difference\n");
        printf(" -            ------           -------        ----------\n");
        // range = [1, 10), step = 0.1
        for (double i = 1.0; i < 10.0; i += 0.1) {
            printf(
                "%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcTan(i), atan(i), arcTan(i) - atan(i));
        }
    }
    if (logorithm == 1) {
        printf(" x            Log              Library        Difference\n");
        printf(" -            ------           -------        ----------\n");
        // range = [1, 10), step = 0.1
        for (double i = 1.0; i < 10.0; i += 0.1) {
            // credit to Wednesday 10am section on 4/14 for number formatting
            printf("%7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
        }
    }
}
