#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main(void)
{
    // define variables to store parameters
    double a, b, c, d, e, f;

    // print prompt
    printf("ax+by=c\n");
    printf("dx+ey=f\n");
    printf("Enter a b c d e f: ");

    // get user input
    scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);

    // conditionals
    if (std::abs(a * e - b * d) < 0.000001)
    {
        printf("No solution.");
    }
    else
    {
        double x = (e * c - b * f )/(a * e - b * d);
        double y = (a * f - c * d )/(a * e - b * d);
        printf("x = %f y = %f\n", x, y);
    }
}