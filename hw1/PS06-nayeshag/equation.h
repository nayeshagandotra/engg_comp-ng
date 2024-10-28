#ifndef EQUATION_H
#define EQUATION_H

class Equation
{
    public:
        float a, b, c; // Coefficients for the equation ax + by = c

        void Plot(float r, float g, float b);        // Simulate plotting by printing values for a given x range
};

class SimultaneousEquation
{
    public:
        Equation eqn[2]; // Array of two Equation objects

        bool Solve(double &x, double &y);       // Solve the system of equations
        void Plot();
};

class Axes
{
    public:
        void Draw();
};

#endif // EQUATION_H
