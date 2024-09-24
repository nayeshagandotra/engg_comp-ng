#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"

void Drawcircle(double cx, double cy, double rad, int fill)
{
    const double YS_PI=3.1415927;
    int total_Segments = 64; 

    if(0!=fill)
    {
        glBegin(GL_POLYGON);
    }
    else{
        glBegin(GL_LINE_LOOP);
    }

    
    for(int i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32;
        double x=cx+cos(angle)*rad;
        double y=cy+sin(angle)*rad;
        glVertex2d(x,y);
    }
    glEnd();
}

void DrawRandomCircle(void)
{
    int cx,cy,rad;
    int r,g,b;
    cx=rand()%800;
    cy=rand()%600;
    rad=rand()%400;
    r=rand()%256;
    g=rand()%256;
    b=rand()%256;
    glColor3ub(r,g,b);
    Drawcircle(cx,cy,rad,0);
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

void DrawRect2(int x1,int y1,int x2,int y2,int fill)
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

void DrawRect3(int x1,int y1,int x2,int y2,int fill)
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

void DrawRect4(int x1,int y1,int x2,int y2,int fill)
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

/*void DrawTri(int coord[],int fill)
{
 if(0!=fill)
    {
        glBegin(GL_TRIANGLES);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    int i;
    for(i=0; i<3; i++);
    {
        glVertex2i(coord[i*2],coord[i*2+1]);
    }
}
*/
int main(void)
{

    FsOpenWindow(0,0,729,507,0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    for(;;)
    {
        FsPollDevice();

        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            break;
        }
        double coord;
        Drawcircle(327,137,20, 1);    
        DrawRect(207 , 176, 444, 471, 0);
        DrawRect2(242, 207, 310, 300, 1);
        DrawRect3(355,207, 427, 300, 1);
        DrawRect3(293,343, 370, 472, 1);
        // DrawTri(coord[204,174, 326,68,443,175], 0);

        glFlush();
    }
}