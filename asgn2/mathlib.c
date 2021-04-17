#include "mathlib.h"

#include <math.h> //only for using sin and cos
#include <stdio.h>

#define EPSILON 1e-10

// Declare helper functions
double Abs(double x);
double Exp(double x);
double Sqrt(double x);

/* HELPER FUNCTIONS */

// Given by Dr Long on Piazza: @69: https://piazza.com/class/kmfs2bmdr9syz?cid=69
// Returns e^x
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

// Sourced from Dr Long on Piazza @256: https://piazza.com/class/kmfs2bmdr9syz?cid=256
// Takes square root of x
double Sqrt(double x) {
    double m, l = 0.0, h = (x < 1) ? 1 : x;
    do {
        m = (l + h) / 2.0;
        if (m * m < x) {
            l = m;
        } else {
            h = m;
        }
    } while (Abs(l - h) > EPSILON);
    return m;
}

// Takes absolute value of x
double Abs(double x) {
    return ((x < 0) ? (-1 * x) : x);
}

double arcSin(double x) {
    double new = x;
    double old = 0.0;
    while (Abs(new - old) > EPSILON) {
        old = new;
        new = old - ((sin(old) - x) / cos(old));
    }
    return new;
}
double arcCos(double x) {
    double result;
    result = (M_PI / 2) - arcSin(x);
    return result;
}
double arcTan(double x) {
    double result;
    result = arcSin(x / Sqrt(x * x + 1));
    return result;
}

double Log(double x) {
    double new = 1.0;
    double old = 0.0;
    while (Abs(new - old) > EPSILON) {
        old = new;
        new = old + ((x - Exp(old)) / Exp(old));
    }
    return new;
}
