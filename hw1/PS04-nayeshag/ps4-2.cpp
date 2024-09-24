#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>

const double YsPI=3.1415927;
double dt=0.025;
double g=98;   //9.8m/s = 98px/s

// define colours
int red[3] = {255, 0, 0};
int green[3] = {0, 255, 0};
int yellow[3] = {255, 255, 0};
int cyan[3] = {0, 255, 255};
int blue[3] = {0, 0, 255};
int magenta[3] = {255, 0, 255};

void DrawRect(int xc,int yc,int w,int h,int colours[3])
{
    glColor3ub(colours[0], colours[1], colours[2]); // yelow
    glBegin(GL_QUADS);
    glVertex2i(xc-w/2,yc-h/2);
    glVertex2i(xc+w/2,yc-h/2);
    glVertex2i(xc+w/2,yc+h/2);
    glVertex2i(xc-w/2,yc+h/2);
    glEnd();
}

void DrawCannon(double cx,double cy, int colours[3])
{
    glColor3ub(colours[0], colours[1], colours[2]);
    double r = 5;
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0; i<360; i+=5)
	{
		double a=(double)i*YsPI/180.0;

		double x=cx+cos(a)*r;
		double y=cy+sin(a)*r;

		glVertex2d(x,y);
	}
	glEnd();
}

void DrawShooter(double theta)
{
    int xc = 20;
    int yc = 580;
    int w = 10;
    int h = 10;
    int l = 20;

    glColor3ub(0, 0, 255); // blue 

    glBegin(GL_QUADS);
    glVertex2i(xc-w/2,yc-h/2);
    glVertex2i(xc+w/2,yc-h/2);
    glVertex2i(xc+w/2,yc+h/2);
    glVertex2i(xc-w/2,yc+h/2);
    glEnd();

    // draw line for shooter
    glBegin(GL_LINES);
    glVertex2d(xc, yc);  
    glVertex2d(xc + l * cos(theta * YsPI / 180.0), yc + l * sin(theta * YsPI / 180.0));  
    glEnd();

}

bool CheckCollision(int mx,int my,int tx,int ty,int tw,int th)
{
	return (tx-tw/2<=mx && mx<=tx+tw/2 && ty-th/2<=my && my<=ty+th/2);
}

int main(void)
{
	srand(time(nullptr));
    int cannon_colours[5][3] = {
        {0, 0, 255},
        {0, 255, 255},
        {255, 255, 0},
        {255, 0, 255},
        {255, 0, 0}
    };

    // init vars for shooter
    static double theta = 45;

    // init counter for num of cannonballs done
    int num_cannonballs = -1;
    int tailx[10];
    int taily[10];
    int frame_index = 0;
    bool mState = false;
    double mvx = 0;     //40m/s = 400px/sec
    double mvy = 0;
    double mx = 0;
    double my = 0;


    // draw target
    // init variables for target
    int xct = 750;
    int yct = 50;
    int wt = 100;
    int ht = 100;
    int tv = 2.5;     //2.5 px/frame = 10m/s

    // draw 5 obstacles //
    // pick 5 random widths
    int obs_table[5][4]; //w,h,xc,yc
    int hit_count[5] = {0,0,0,0,0};
    bool checked_collision[5] = {false, false, false, false, false};

    for (int i = 0; i <5; i++){
        obs_table[i][0]=rand()%80;
        obs_table[i][1]=rand()%150;
        obs_table[i][2]=60 + rand() % (760 - 60 + 1);
        obs_table[i][3]=75 + rand() % (525 - 75 + 1);
        //debug
        // std::cout << obs_table[i][0] << " " << obs_table[i][1] << " " << obs_table[i][2] << " " <<obs_table[i][3] << std::endl;
    }
    // draw cannon 
    // draw cannonball

    
	FsOpenWindow(0,0,800,600,1);

    for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
        
		if(FSKEY_ESC==key || num_cannonballs > 5)
		{
			break;
		}

        switch(key)
		{
		case FSKEY_UP:
			theta += 3.0;
            theta = std::min(theta, 90.0);
			break;
		case FSKEY_DOWN:
			theta-=3.0;
            theta = std::max(theta, 0.0);
			break;
        case FSKEY_SPACE:
			if(true!=mState)
			{
				mState=true;
                num_cannonballs += 1;
				mx=20 + 20 * cos(-theta * YsPI / 180.0);    //start cannonball at 
				my=580 + 20 * sin(-theta * YsPI / 180.0);
                mvx = 400* cos(-theta * YsPI / 180.0);
                mvy = 400* sin(-theta * YsPI / 180.0);
			}
			break;
		}

        if(true==mState)     //this is the logic for moving the cannonball
		{
			mx += mvx*dt;
            my += mvy*dt;
            mvy += g*dt;

            // std::cout << mvx << " " << mx << std::endl;

			if(my<0 || my > 600 || mx > 800 || mx < 0)
			{
				mState=false;
                mvx = 400* cos(-theta * YsPI / 180.0);
                mvy = 400* sin(-theta * YsPI / 180.0);
			}
		}


        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // put this in rendering for loop, before drawings

        // draw shooter
        DrawShooter(-theta);

        if(true==mState)
		{
			DrawCannon(mx,my, cannon_colours[num_cannonballs]);

		}
        
        // update velocity if too close
        if (yct == 550 && tv > 0 || yct == 50 && tv < 0){
            tv = -tv;
        }
        // update target specs
        yct += tv;

        // draw 5 obstacles
        for (int i = 0; i <5; i++){
            if (hit_count[i] == 0){
                DrawRect(obs_table[i][2], obs_table[i][3], obs_table[i][0], obs_table[i][1], green);
            }
            else if (hit_count[i] == 1){
                DrawRect(obs_table[i][2], obs_table[i][3], obs_table[i][0], obs_table[i][1], yellow);
            }
            else if (hit_count[i] > 1){
                continue;
            }
            if (CheckCollision(mx, my, obs_table[i][2], obs_table[i][3], obs_table[i][0], obs_table[i][1])){
                hit_count[i] += 1;
                mState = false;
                mx=20 + 20 * cos(-theta * YsPI / 180.0);    //start cannonball at 
				my=580 + 20 * sin(-theta * YsPI / 180.0);
            };
            // std::cout << hit_count[i] << " " << mx << std::endl;
            
        }
        // draw target
        DrawRect(xct, yct, wt, ht, red);
        FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.

		FsSleep(25);
    }
    return 0;
}
