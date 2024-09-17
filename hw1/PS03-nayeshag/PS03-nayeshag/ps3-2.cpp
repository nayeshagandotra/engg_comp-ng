#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"


const double YsPI=3.1415927;

// Function to draw a circle and radiating lines
void DrawRadiatingLines(int cx, int cy, int r1, int r2)
{
    int numSegments = 360; // Circle resolution

    // Draw the circle
    glBegin(GL_LINE_LOOP);
	for(int i=0; i<360; i+=5)
	{
		double a=(double)i*YsPI/180.0;

		double x=cx+cos(a)*r1;
		double y=cy+sin(a)*r1;

		glVertex2d(x,y);
	}
	glEnd();

    // Draw the radiating lines every 60 degrees
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 60)
    {
        double theta = double(i) * YsPI / 180.0; // Convert angle to radians
        double x = cx + r1 * cos(theta);   // x-coordinate of the point on the circumference
        double y = cy + r1 * sin(theta);   // y-coordinate of the point on the circumference
        
		double endx = cx + r2 * cos(theta);
		double endy = cy + r2 * sin(theta);
		glVertex2d(x, y);                    // Start point (center of the circle)
        glVertex2d(endx, endy);                      // End point (on the circumference)
    }
    glEnd();
}

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

void DrawEllipse90cut(double cx,double cy,double r1, double r2)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<360; i+=5)
	{
		double a=(double)i*YsPI/180.0;

		if (i <= 90 || i >= 180){
			double x=cx+cos(a)*r1;
			double y=cy+sin(a)*r2;

			glVertex2d(x,y);
		}
	}
	glEnd();
}

void DrawRect(int x1,int y1,int x2,int y2,int fill)
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
        int circles[5][3] = {
            {349, 141, 100/2},
            {349, 141, 160/2},
            {349, 141, 200/2},
            {349, 141, 100/2},
            {300, 288, 550/2}
        };

		int ellipses[3][4] = {
        {300, 288, 201/2, 550/2},
        {300, 288, 370/2, 550/2},
        {300, 288, 420/2, 550/2},
    	};

        for (int i = 0; i < 6; i++) {
            DrawCircle(circles[i][0],circles[i][1],circles[i][2]);
        }

		DrawRadiatingLines(349, 141, 56/2, 100/2);

		DrawEllipse(ellipses[2][0],ellipses[2][1],ellipses[2][2], ellipses[2][3]);
		DrawEllipse90cut(ellipses[0][0],ellipses[0][1],ellipses[0][2], ellipses[0][3]);
		DrawEllipse90cut(ellipses[1][0],ellipses[1][1],ellipses[1][2], ellipses[1][3]);
		
		DrawRect((300-550/2) , 288 - (35/2), (300+550/2), 288 + (35/2), 1);

		glFlush();
	}
}


