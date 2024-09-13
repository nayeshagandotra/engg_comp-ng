#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"

const double YsPI=3.1415927;

void DrawCircle(double cx,double cy,double r)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<360; i+=5)
	{
		double a=(double)i*YsPI/180.0;

		double x=cx+cos(a)*r;
		double y=cy+sin(a)*r;

		glVertex2d(x,y);
	}
	glEnd();
}

void DrawEllipse(double cx,double cy,double r1, double r2)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<360; i+=5)
	{
		double a=(double)i*YsPI/180.0;

		double x=cx+cos(a)*r1;
		double y=cy+sin(a)*r2;

		glVertex2d(x,y);
	}
	glEnd();
}

void DrawRect(int x1,int y1,int x2,int
y2,int fill)
{
    if(0!=fill)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);
    glEnd();
}

int main(void)
{

	FsOpenWindow(0,0,600,566,0);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}
        int circles[6][3] = {
            {349, 141, 56},
            {349, 141, 100},
            {349, 141, 160},
            {349, 141, 200},
            {349, 141, 100},
            {300, 288, 550}
        };

        for (int i = 0; i < 6; i++) {
            DrawCircle(circles[i][0],circles[i][1],circles[i][2]);
        }
		glFlush();
	}
}


