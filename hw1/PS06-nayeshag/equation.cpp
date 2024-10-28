#include "equation.h"
#include <iostream>
#include <cmath>
#include "fssimplewindow.h"

const double tolerance=1e-6;

// plot equation using fssimplewindow
void Equation::Plot(float red, float green, float blue)
{
    int x_int;
    int y_int;

    glColor3ub(red,green,blue);

    glBegin(GL_LINES);
    if (b == 0 && a!= 0){
        x_int = c/a;
        // std::cout << "here!1" << std::endl;
        glVertex2i(300+x_int*10,0);
        glVertex2i(300+x_int*10,600);
    }
    else if (b != 0 && a== 0){
        y_int = c/b;
        // std::cout << "here!2" << std::endl;
        glVertex2i(0, 300+y_int*10);
        glVertex2i(600, 300+y_int*10);
    }
    else if (b != 0 && a!= 0){
        // std::cout << "here!3" << std::endl;
        x_int = c/a;
        y_int = c/b;
        glVertex2i(0, -(((c+30*a)/b)*10-300));
        glVertex2i(600, -(((c-30*a)/b)*10-300));
    }
    else{
        // plot a dot at 0
        std::cout << "Invalid equation initialized. Use non-zero coefficients" << std::endl;
    }
    glEnd();
}


// Solve method for SimultaneousEquation
bool SimultaneousEquation::Solve(double &x, double &y)
{
    float  D=eqn[0].a*eqn[1].b-eqn[0].b*eqn[1].a;
    if(fabs(D)<tolerance)
    {
        return false;
    }
    else
    {
        x=(eqn[1].b*eqn[0].c-eqn[0].b*eqn[1].c)/D;
        y=(eqn[0].a*eqn[1].c-eqn[0].c*eqn[1].a)/D;
        return true;
    }
}

void SimultaneousEquation::Plot(){
    eqn[0].Plot(255,0,0);
    eqn[1].Plot(0,0,255);
}

void Axes::Draw(){

    // draw grid lines vertical
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_LINES);
    for (int i=0; i <20; i++){
        glVertex2i(i*30,0);
        glVertex2i(i*30,600);
    }
    glEnd();

    // draw grid lines horizontal
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_LINES);
    for (int i=0; i <20; i++){
        glVertex2i(0, i*30);
        glVertex2i(600, i*30);
    }
    glEnd();

    // draw main axes
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2i(300,0);
    glVertex2i(300,600);
    glVertex2i(0,300);
    glVertex2i(600,300);
    glEnd();
}
