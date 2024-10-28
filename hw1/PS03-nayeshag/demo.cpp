#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "mmlplayer.h"

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
int black[3] = {0, 0, 0};
int tan_col[3] = {204, 204, 76};
int sky_blue[3] = {135, 206, 235};
int orange[3] = {255, 165, 0};
int ds_col[3] = {0, 0, 0};

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

void DrawCircleFilled(double cx,double cy,double r)
{
	glBegin(GL_TRIANGLE_FAN);
    glVertex2d(cx, cy); // Center of the circle
    for(int i = 0; i <= 360; i += 5)
    {
        double angle = (double)i * YsPI / 180.0;
        double x = cx + cos(angle) * r;
        double y = cy + sin(angle) * r;
        glVertex2d(x, y);
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

void DrawXWing(float x, float y, float size, float theta)
{
    // Isolate transformations for the X-Wing
    glPushMatrix();

    // Move to the position (x, y) and apply rotation around the Z-axis (2D rotation)
    glTranslatef(x, y, 0.0f); 
    glRotatef(90-theta, 0.0f, 0.0f, 1.0f);  // Rotate the X-Wing by 'theta' degrees

    // X-Wing dimensions based on the size parameter
    float wingLength = size * 40;
    float bodyLength = size * 10;
    float bodyWidth = size * 10;
    float wingWidth = size * 25;
    float engineRadius = size * 6;  // Circle size for the engines
    float engineOffset = size * 20; // Adjusted to bring engines closer to the body

    // Draw the pointed tip of the X-Wing
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 255, 255); 
    glVertex2f(0, 0);  // Nose point at the tip (origin after translation)
    glVertex2f(-bodyWidth / 2, 10); // Bottom-left of the body
    glVertex2f(bodyWidth / 2, 10);  // Bottom-right of the body
    glEnd();

    // Draw the wings
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 0, 0); // Red color for the wings
    // Left Wing
    glVertex2f(0, bodyLength);          // Top point of left wing
    glVertex2f(-wingLength, bodyLength - wingWidth); // Left wing tip
    glVertex2f(-wingLength, bodyLength + wingWidth); // Left wing base

    // Right Wing
    glVertex2f(0, bodyLength);          // Top point of right wing
    glVertex2f(wingLength, bodyLength - wingWidth); // Right wing tip
    glVertex2f(wingLength, bodyLength + wingWidth); // Right wing base
    glEnd();

    // Draw the circular engines at the end of each wing (closer to the body)
    glColor3ub(100, 100, 255); // Blue color for the engines
    // Left engines (closer to the body)
    DrawCircle(-engineOffset, bodyLength - wingWidth, engineRadius); // Left engine upper
    DrawCircle(-engineOffset, bodyLength + wingWidth, engineRadius); // Left engine lower
    // Right engines (closer to the body)
    DrawCircle(engineOffset, bodyLength - wingWidth, engineRadius); // Right engine upper
    DrawCircle(engineOffset, bodyLength + wingWidth, engineRadius); // Right engine lower

    // Reset the transformations
    glPopMatrix();
}

void DrawYWing(int cx, int cy, float scale)
{
    // Define colors (RGB values from 0.0 to 1.0)
    float bodyColor[3] = {0.8f, 0.8f, 0.3f};  // Light tan for body
    float cockpitColor[3] = {0.5f, 0.5f, 0.2f}; // Darker tan for cockpit
    float engineColor[3] = {0.6f, 0.6f, 0.6f}; // Gray for engines
    float connectorColor[3] = {0.4f, 0.4f, 0.4f}; // Dark gray for connectors

    // Main Body (fuselage)
    int bodyWidth = int(40 * scale);
    int bodyHeight = int(160 * scale);
    int bodyX1 = cx - bodyWidth / 2;
    int bodyY1 = cy - bodyHeight / 2;

    // Cockpit (top of the body)
    int cockpitWidth = int(20 * scale);
    int cockpitHeight = int(40 * scale);
    int cockpitX1 = cx - cockpitWidth / 2;
    int cockpitY1 = bodyY1 - cockpitHeight;

    // Left Engine
    int engineWidth = int(20 * scale);
    int engineHeight = int(140 * scale);
    int leftEngineX1 = cx - bodyWidth / 2 - 60 * scale;  // Offset from body
    int leftEngineY1 = cy - engineHeight / 2;

    // Right Engine
    int rightEngineX1 = cx + bodyWidth / 2 + 40 * scale; // Offset from body
    int rightEngineY1 = leftEngineY1;

    // Connectors (from body to engines)
    int connectorWidth = int(10 * scale);
    int connectorLength = int(60 * scale);

    // Draw main body
    glColor3f(bodyColor[0], bodyColor[1], bodyColor[2]);
    glBegin(GL_QUADS);
    glVertex2i(bodyX1, bodyY1);
    glVertex2i(bodyX1 + bodyWidth, bodyY1);
    glVertex2i(bodyX1 + bodyWidth, bodyY1 + bodyHeight);
    glVertex2i(bodyX1, bodyY1 + bodyHeight);
    glEnd();

    // Draw cockpit
    glColor3f(cockpitColor[0], cockpitColor[1], cockpitColor[2]);
    glBegin(GL_QUADS);
    glVertex2i(cockpitX1, cockpitY1);
    glVertex2i(cockpitX1 + cockpitWidth, cockpitY1);
    glVertex2i(cockpitX1 + cockpitWidth, cockpitY1 + cockpitHeight);
    glVertex2i(cockpitX1, cockpitY1 + cockpitHeight);
    glEnd();

    // Draw left engine
    glColor3f(engineColor[0], engineColor[1], engineColor[2]);
    glBegin(GL_QUADS);
    glVertex2i(leftEngineX1, leftEngineY1);
    glVertex2i(leftEngineX1 + engineWidth, leftEngineY1);
    glVertex2i(leftEngineX1 + engineWidth, leftEngineY1 + engineHeight);
    glVertex2i(leftEngineX1, leftEngineY1 + engineHeight);
    glEnd();

    // Draw right engine
    glBegin(GL_QUADS);
    glVertex2i(rightEngineX1, rightEngineY1);
    glVertex2i(rightEngineX1 + engineWidth, rightEngineY1);
    glVertex2i(rightEngineX1 + engineWidth, rightEngineY1 + engineHeight);
    glVertex2i(rightEngineX1, rightEngineY1 + engineHeight);
    glEnd();

    // Draw connectors (left)
    glColor3f(connectorColor[0], connectorColor[1], connectorColor[2]);
    glBegin(GL_QUADS);
    glVertex2i(cx - bodyWidth / 2, cy - connectorWidth / 2);
    glVertex2i(cx - bodyWidth / 2 - connectorLength, cy - connectorWidth / 2);
    glVertex2i(cx - bodyWidth / 2 - connectorLength, cy + connectorWidth / 2);
    glVertex2i(cx - bodyWidth / 2, cy + connectorWidth / 2);
    glEnd();

    // Draw connectors (right)
    glBegin(GL_QUADS);
    glVertex2i(cx + bodyWidth / 2, cy - connectorWidth / 2);
    glVertex2i(cx + bodyWidth / 2 + connectorLength, cy - connectorWidth / 2);
    glVertex2i(cx + bodyWidth / 2 + connectorLength, cy + connectorWidth / 2);
    glVertex2i(cx + bodyWidth / 2, cy + connectorWidth / 2);
    glEnd();
}

void DrawDeathStar(int cx, int cy, float scale)
{
    
    // Circles for the Death Star (rescaled to fit 100x100)
    int circles[5][3] = {
        {int(349 * scale) + cx, int(141 * scale) + cy, int(100 * scale) / 2},
        {int(349 * scale) + cx, int(141 * scale) + cy, int(160 * scale) / 2},
        {int(349 * scale) + cx, int(141 * scale) + cy, int(200 * scale) / 2},
        {int(349 * scale) + cx, int(141 * scale) + cy, int(100 * scale) / 2},
        {int(300 * scale) + cx, int(288 * scale) + cy, int(550 * scale) / 2}
    };

    // Ellipses for the Death Star (rescaled to fit 100x100)
    int ellipses[3][4] = {
        {int(300 * scale) + cx, int(288 * scale) + cy, int(201 * scale) / 2, int(550 * scale) / 2},
        {int(300 * scale) + cx, int(288 * scale) + cy, int(370 * scale) / 2, int(550 * scale) / 2},
        {int(300 * scale) + cx, int(288 * scale) + cy, int(420 * scale) / 2, int(550 * scale) / 2}
    };

    // Draw the circles
    for (int i = 0; i < 4; i++) {
        DrawCircle(circles[i][0], circles[i][1], circles[i][2]);
    }

    // Draw the radiating lines (rescaled to fit 100x100)
    DrawRadiatingLines(int(349 * scale) + cx, int(141 * scale) + cy, int(56 * scale) / 2, int(100 * scale) / 2);

    // Draw the ellipses (rescaled)
    DrawEllipse(ellipses[2][0], ellipses[2][1], ellipses[2][2], ellipses[2][3]);
    DrawEllipse90cut(ellipses[0][0], ellipses[0][1], ellipses[0][2], ellipses[0][3]);
    DrawEllipse90cut(ellipses[1][0], ellipses[1][1], ellipses[1][2], ellipses[1][3]);

    // Draw the trench (rectangle) (rescaled and translated)
    // DrawRect(cx - int(550 * scale) / 2, cy - int(35 * scale) / 2, cx + int(550 * scale) / 2, cy + int(35 * scale) / 2, 1);
    DrawRect(int(300 * scale) + cx , int(288 * scale) + cy, int(550 * scale), int(50 * scale), black);
    // Draw the outer circle for the Death Star (rescaled)
    DrawCircle(circles[4][0], circles[4][1], circles[4][2]);
}

bool CheckCollision(int mx,int my,int tx,int ty,int tw,int th)
{
	return (tx-tw/2<=mx && mx<=tx+tw/2 && ty-th/2<=my && my<=ty+th/2);
}

void DrawText(double xtext, double ytext, const char *text, int fontsize, int colours[3]){
    // Set the color for the text (RGB)
    glColor3ub(colours[0], colours[1], colours[2]);
    
    // Set the position for the text
    glRasterPos2i(xtext, ytext);  // Position at x=100, y=300
    
    switch (fontsize)
    {
        case 32:
            // Use one of the bitmap fonts to render a string
            YsGlDrawFontBitmap32x48(text);  // Drawing with 8x12 font
            break;
        case 16:
            YsGlDrawFontBitmap16x20(text);  // Drawing with 8x12 font
            break;
        case 8:
            YsGlDrawFontBitmap8x8(text);  // Drawing with 8x12 font
            break;
    }
}

void DrawBG(){
    glShadeModel(GL_SMOOTH);

    
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0); // yelow
    glVertex2i(400-800/2,300-600/2);

    glColor3ub(25, 25, 25); // yelow
    glVertex2i(400+800/2,300-600/2);

    glColor3ub(51, 51, 51);
    glVertex2i(400+800/2,300+600/2);

    glColor3ub(76, 76, 76);
    glVertex2i(400-800/2,300+600/2);
    glEnd();
    // DrawRect(400, 300, 800, 600, black);
    
    // Loop to place * symbols at uniformly spaced positions
    for (int y = 50; y < 600; y += 50)  // Step every 50 pixels in the y direction
    {
        for (int x = 50; x < 800; x += 50)  // Step every 50 pixels in the x direction
        {
            DrawText(x, y, "*", 8, yellow);  // Render * at each grid position
        }
    }
}

void DrawHeart(int cx, int cy, float scale)
{
    glBegin(GL_TRIANGLE_FAN);
    
    // Set the color for the heart
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color

    // Draw the heart shape using a parametric equation
    for (float angle = 0; angle <= 2 * YsPI; angle += 0.01f) {
        // Parametric equations for heart shape
        float x = 16 * pow(sin(angle), 3);
        float y = -(13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle)); // Flip y

        // Scale and translate the heart
        glVertex2f(cx + x * scale, cy + y * scale);
    }

    glEnd();
}

void DrawSwayingGrass(int w, int h, double time)
{
    const int grassHeight = 110;
    const int numBlades = 50;
    const double swayAmplitude = 5.0;
    const double swayFrequency = 0.02;
    int forest_green[3] = {34, 139, 34};

    glColor3ub(34, 139, 34); // Forest green color
    DrawRect(400, 600, 800, 90, forest_green);

    for (int i = 0; i < numBlades; ++i)
    {
        double x = (double)i / numBlades * w;
        double sway = sin(time*swayFrequency + i * 0.3) * swayAmplitude;

        glBegin(GL_TRIANGLE_STRIP);
        glVertex2d(x, h);
        glVertex2d(x + sway, h - grassHeight);
        glVertex2d(x + 70, h);
        glEnd();
    }
}

void DrawBB8Body(float x, float y, float theta)
{
    theta = theta * YsPI / 180.0;

    // Body
    glColor3ub(255, 165, 0); // Orange
    DrawCircleFilled(x, y, 70); // Main body

    // Details on the body
    glColor3ub(0, 0, 0); // white
    DrawRadiatingLines(x + 30*cos(theta), y + 30*sin(theta), 10, 17); // Detail circle

}

void DrawBB8Head(float x, float y)
{
    float scale = 1.5;

    // Antenna
    DrawRect(x+8, y-75*scale, 5, 40, black);

    // Head
    glColor3ub(255, 255, 255); // White
    DrawCircleFilled(x, y - 50 * scale, 25 * scale); // Head

    // Eye
    glColor3ub(0, 0, 0); // Black
    DrawCircleFilled(x, y - 50 * scale - 10 * scale, 10 * scale); // Eye
    glColor3ub(255, 0, 0); // red
    DrawCircleFilled(x-7, y - 50 * scale - 10 * scale + 7, 3 * scale); // Eye

}

void DrawLaserBeam(float x, float y, float angle, float length)
{
    glColor3ub(255, 255, 0); // Red color for the laser
    float halfWidth = 2.5f; // Half of the width (5 / 2)
    angle = angle * YsPI / 180.0;

    // Calculate the perpendicular vector for width
    float dx = cos(angle);
    float dy = sin(angle);

    glBegin(GL_QUADS);
    glVertex2f(x - dy * halfWidth, y + dx * halfWidth);
    glVertex2f(x + dy * halfWidth, y - dx * halfWidth);
    glVertex2f(x + dx * length + dy * halfWidth, y + dy * length - dx * halfWidth);
    glVertex2f(x + dx * length - dy * halfWidth, y + dy * length + dx * halfWidth);
    glEnd();
}

void DrawNet(float x, float y, float scale)
{
    DrawRadiatingLines(x, y, 20*scale, 40*scale);
    DrawRadiatingLines(x, y, 40*scale, 60*scale);
    DrawRadiatingLines(x, y, 60*scale, 80*scale);
}

int main(void)
{
    // audio things
    MMLSegmentPlayer mmlplayer;

    // mmlplayer.AddSegment(
    // "@2T120L4V15",  // Set tempo to 120 BPM, note length to quarter, volume to 12
    // "@2T120L2S0M6000",  // Starting silence
    // ""  // End of segment
    // );
    // mmlplayer.AddSegment("O3D4S4O3D4S4O3D4S4O3G2", "");  // D3_t1, D3_t1, D3_t1, G3_t4
    // mmlplayer.AddSegment("O4D2S4O4C4S4O3B4S4O3A4S4", "");  // D4_t4, C4_t1, B3_t1, A3_t1
    // mmlplayer.AddSegment("O4G2S4O4D1S4O4C4S4O3B4S4O3A4", "");  // G4_t4, D4_t2, C4_t1, B3_t1, A3_t1
    // mmlplayer.AddSegment("O4G2S4O4D1S4O4C4S4O3B4S4O3A4", "");  // G4_t4, D4_t2, C4_t1, B3_t1, C4_t1
    // mmlplayer.AddSegment("O3A2S4O3D1S4O3D4S4O3E3S4", "");  // A3_t4, D3_t2, D3_t1, E3_t3
    // mmlplayer.AddSegment("O3E1S4O4C1S4O3B1S4O3A1", ""); // E3_t2, C4_t2, B3_t2, A3_t2


    // YsSoundPlayer player;
	// player.Start();

    // YsSoundPlayer::Stream stream;
	// YsSoundPlayer::StreamingOption streamOpt;
	// streamOpt.ringBufferLengthMillisec=4000;
	// player.StartStreaming(stream,streamOpt);

	// YsSoundPlayer::SoundData nextWave;
	// auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
	// nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

	// if(0!=mmlplayer.GetLastErrorCode())
	// {
	// 	for(auto msg : mmlplayer.GetLastError().Format())
	// 	{
	// 		std::cout << msg << std::endl;
	// 	}
	// }
    FsChangeToProgramDir();
    YsSoundPlayer player;
    YsSoundPlayer::SoundData wav;
    if(YSOK!=wav.LoadWav("sasta_starwars.wav"))
    {
        printf("Failed to read \n");
        return 1;
    }

    player.Start();
    player.PlayOneShot(wav);
    // while(YSTRUE==player.IsPlaying(wav))
    // {
    //     player.KeepPlaying();
    // }
    // player.End();


    // init common vars
	srand(time(nullptr));
    int num_cannonballs = -1;
    int state = 0;
    int iter = 0;
    int xtext = 0;
    int ytext = 200;
    int vytext = -2;  //10px/frame
    std::vector<std::string> start_message;

    start_message.push_back("A long time ago,"); 
    start_message.push_back("in a galaxy ");
    start_message.push_back("far, far away...");
    start_message.push_back("                             ");
    start_message.push_back("Two planes in love ");
    start_message.push_back("have had a quarrel");
    start_message.push_back("Y won't speak to X");
    start_message.push_back("ever again, unless");
    start_message.push_back("X can get her the one");
    start_message.push_back("thing her heart desires...");
    start_message.push_back("the death star!");
    start_message.push_back("Only you can help");
    start_message.push_back("X win Y back");
    start_message.push_back("Are you ready to fight...");
    start_message.push_back("...For love?");

    std::vector<std::string> xwingbb8convo;
    xwingbb8convo.push_back("                             ");
    xwingbb8convo.push_back("What happened X? You look so stressed!");
    xwingbb8convo.push_back("Y is angry with me");
    xwingbb8convo.push_back("and won't speak with me again");
    xwingbb8convo.push_back("unless I get her the death star!");
    xwingbb8convo.push_back("But I have no idea where it is!");
    xwingbb8convo.push_back("Oh you mean that death star?");
    xwingbb8convo.push_back("The one that's flying away right now?");
    xwingbb8convo.push_back("YES! I will hunt you down, Death Star!");

    std::vector<std::string> end_message;

    end_message.push_back("My love, I have destroyed the death star for you!");
    end_message.push_back("X Wing, Y Wing, Y Wait, Be Mine~");
    end_message.push_back("Your heroism has won me, I forgive you!   ");


    // init vars for shooter
    static double theta = 45;

    int frame_index = 0;
    int col_frame_index = 0;
    int text_number = 0;

    // missile things (to change)
    bool mState = false;
    double mvx = 0;     //40m/s = 400px/sec
    double mvy = 0;
    double mx = 0;
    double my = 0;

    // init variables for target
    int tx = 200;
    int ty = 120;
    int tvy = -2;     //2.5 px/frame = 10m/s
    int tvx = -2;     //2.5 px/frame = 10m/s

    // init variables for bb8
    int rvbb8 = 1;  //5 degrees per frame
    int bb8angle = 45;
    int tvxbb8 = 10; //2 px/frame (slow boi)
    int bb8x = 0; //start from out of frame

    // init vars for xwing
    int tvxxwing = 2;
    int tvyxwing = 1;
    int xwingy = 200;
    int xwingx = 0;
    int tempxwingy = 520;
    int rvxwing = -1;

    // init vars for net
    int netx = 60;
    int nety = 520;
    int netvel = 1;

    // init variables for death star (in static frame)
    int tvyds = -5;
    int dsx = 600;
    int dsy = 600;
    bool drawds = false;


    bool deathstar_hit = false;

    double time = 0.0;
    

	FsOpenWindow(0,0,800,600,1);

    for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();
        
		if(FSKEY_ESC==key)
		{
			break;
		}
        switch(key)
		{
        case FSKEY_ENTER:
            state += 1;
            std::cout << state <<std::endl;
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // put this in rendering for loop, before drawings

        // insert frame specific things 
        switch(state){
            case 0:
                // make background
                DrawBG();
                // Print the strings
                for(int i = 0; i < start_message.size(); i++) {
                   DrawText(xtext, ytext + 48*i, start_message[i].c_str(), 32, yellow);
                }
                ytext += vytext;

                // if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
                // {
                //     player.AddNextStreamingSegment(stream,nextWave);
                //     auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
                //     nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

                //     if(0!=mmlplayer.GetLastErrorCode())
                //     {
                //         for(auto msg : mmlplayer.GetLastError().Format())
                //         {
                //             std::cout << msg << std::endl;
                //         }
                //     }
                // }
                player.PlayOneShot(wav);
                
                if (ytext + 48*(int)(start_message.size()) < 300){
                    state+= 1;
                }
                break;
            case 1:
                // Draw the blue skies
                DrawRect(400, 300, 800, 600, sky_blue);

                if (drawds){
                    glColor3ub(ds_col[0],ds_col[0], ds_col[0]);
                    DrawDeathStar(dsx, dsy, 0.3);
                }

                if (bb8x < 500){
                    // draw bb8
                    DrawBB8Body(bb8x, 455, bb8angle);
                    bb8angle += rvbb8;
                    DrawBB8Head(bb8x+7, 455+5);
                    bb8x+= tvxbb8;
                } else{
                    DrawBB8Body(bb8x, 455, bb8angle);
                    DrawBB8Head(bb8x, 455);
                    // wait a littoe bit then bring in the x wing
                    frame_index += 1;
                }

                if (frame_index > 8){

                    DrawXWing(xwingx, xwingy, 2.0f, 90); // Draw X-Wing at (400, 300) with size 1.0
                    if (xwingy == 190 && tvyxwing < 0 || xwingy == 210 && tvyxwing > 0){
                        tvyxwing = -tvyxwing;
                    }
                    xwingy += tvyxwing;
                    if (xwingx < 100){
                        xwingx += tvxxwing;
                    }
                }

               

                switch(text_number){
                    case 0:
                    case 1:
                        DrawText(100, 120, xwingbb8convo[text_number].c_str(), 16, orange);
                        break;
                    case 6:
                    case 7:
                        drawds = true;
                        dsy += tvyds;
                        DrawText(100, 120, xwingbb8convo[text_number].c_str(), 16, orange);
                        break;
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                        DrawText(50, 120, xwingbb8convo[text_number].c_str(), 16, red);
                        break;
                }
                text_number = std::min(frame_index/100, (int)xwingbb8convo.size());

                // Draw the swaying grass
                DrawSwayingGrass(800, 600, time);

                if (text_number == (int)xwingbb8convo.size()){
                    state = 2;
                    frame_index = 0;
                    text_number = 0;
                    xwingy = 520;
                    tvyxwing = 1;
                }

                break;
            case 2:
                // Draw the blue skies
                DrawRect(400, 300, 800, 600, sky_blue);
                DrawXWing(60, tempxwingy, 1.0f, theta); // Draw X-Wing at (400, 300) with size 1.0
                tempxwingy -= tvyxwing;

                DrawText(50, 120, "Die Death Star, Die!", 16, red);
                
                if (tempxwingy == 80 && tvyxwing > 0 || tempxwingy == 520 && tvyxwing < 0){
                        tvyxwing = -tvyxwing;
                }

                if (frame_index > 50 && frame_index < 70){
                    // update target specs
                    ty += tvy;
                    tx += tvx;
                    DrawLaserBeam(60, tempxwingy, -theta, 3000);
                }
                if (frame_index > 70 && frame_index < 116){
                    ty -= tvy;
                    tx -= tvx;
                    theta += rvxwing;
                }
                if (frame_index > 200 && frame_index < 250){
                    // update target specs
                    ty += tvy;
                    tx += tvx;
                    DrawLaserBeam(60, tempxwingy, -theta, 3000);
                }
                if (frame_index > 300 && frame_index < 330){
                    ty -= tvy;
                    tx -= tvx-10;
                    nety = ty;
                }
                if (frame_index > 330){
                    DrawNet(netx, nety, 1.0+ (double)(frame_index / 300));
                    netx+= netvel;
                }

                if (CheckCollision(netx, nety, tx, ty, 100, 100)){
                    netvel = 0;
                    ds_col[0] = 255;
                    if (!deathstar_hit){
                        col_frame_index = frame_index;
                    }
                    deathstar_hit = true;
                };

                // draw targets
                glColor3ub(ds_col[0],ds_col[0], ds_col[0]);
                DrawDeathStar(tx, ty, 0.1);

                if (deathstar_hit && frame_index == col_frame_index+50){
                    state += 1;
                    frame_index = 0;
                }
                frame_index += 1;
                break;
            case 3:
                // make background
                DrawBG();
                DrawXWing(250, 300, 2.0f, 90); // Draw X-Wing at (400, 300) with size 1.0
                DrawYWing(550, 300, 1.0f); // Draw X-Wing at (400, 300) with size 1.0

                switch(text_number){
                    case 0:
                        DrawText(10, 175, end_message[text_number].c_str(), 16, red);
                        break;
                    case 1:
                        DrawText(10, 175, end_message[text_number].c_str(), 16, red);
                        break;
                    case 2:
                        DrawText(50, 175, end_message[text_number].c_str(), 16, tan_col);
                        break;
                    case 3:
                        DrawHeart(400, 300, frame_index*0.01);
                        break;
                    case 4:
                        DrawText(200, 175, "THE END", 32, blue);
                        break;
                    
                }
                frame_index += 1;
                text_number = std::min(frame_index/200, 4);
                break;   
        }
        
        
        FsSwapBuffers(); // FsSwapBuffers() for double-buffered mode, glFlush() for single-buffered mode.
		FsSleep(25);
        time += 1;
    }
    return 0;
}
