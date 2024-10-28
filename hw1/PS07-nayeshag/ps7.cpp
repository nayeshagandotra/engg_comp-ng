#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <fstream>

class CharBitmap {
    
    public: 

    int wid, hei;
    char *pix;

    // Default constructor for empty bitmap
    CharBitmap() : wid(0), hei(0), pix(nullptr) {}

    // Destructor
    ~CharBitmap() {
        CleanUp();
    }

    // CleanUp function
    void CleanUp() {
        delete[] pix;
        pix = nullptr;
        wid = 0;
        hei = 0;
    }

    void Create(int w, int h){
        // clean up any previous instance of the same class
        // to prevent memory leak
        CleanUp();

        // copy w and h to wid and hei
        wid = w;
        hei = h;
        pix = (w * h > 0) ? new char[w * h] : nullptr;
        if (pix) {
            std::fill(pix, pix + w * h, '0');
        }
    }

    void SetPixel(int x, int y, char p){
        if((x >= 0 || x < wid) && (y >= 0 || y < hei)){
            pix[y*wid + x] = p;
        }
       return;
    }

    char GetPixel(int x, int y){
        if((x >= 0 || x < wid) && (y >= 0 || y < hei)){
            return pix[y*wid + x];
        }
        return '0';
    }

    void DrawRect(int xc,int yc,int w,int h,int colours[3])
    {
        glColor3ub(colours[0], colours[1], colours[2]); 
        glBegin(GL_QUADS);
        glVertex2i(xc*20,yc*20);
        glVertex2i(xc*20 + w ,yc*20);
        glVertex2i(xc*20 + w,yc*20 + h);
        glVertex2i(xc*20,yc*20 + h);
        glEnd();
    }

    int* getColour(char p){
        static int* colours = nullptr;
        colours = new int[3];
        colours[0] = 0;
        colours[1] = 0;
        colours[2] = 0;
        // assign colour based on pixel value
        switch(p)
		{
        case '0':
            // all black
            return colours;
        case '1':
            // blue
            colours[0] = 0;
            colours[1] = 0;
            colours[2] = 255;
            return colours;
        case '2':
            // red
            colours[0] = 255;
            colours[1] = 0;
            colours[2] = 0;
            return colours;
        case '3':
            // magenta
            colours[0] = 255;
            colours[1] = 0;
            colours[2] = 255;
            return colours;
        case '4':
            // green
            colours[0] = 0;
            colours[1] = 255;
            colours[2] = 0;
            return colours;
        case '5':
            // cyan
            colours[0] = 0;
            colours[1] = 255;
            colours[2] = 255;
            return colours;
        case '6':
            // yellow
            colours[0] = 255;
            colours[1] = 255;
            colours[2] = 0;
            return colours;
        case '7':
            // white
            colours[0] = 255;
            colours[1] = 255;
            colours[2] = 255;
            return colours;
        }
        return colours;
    }

    void Draw(){
        char p;
        int x,y;
        int* colours;

        for (x = 0; x < wid; x++){
            for (y = 0; y < hei; y++){
                // draw pixel as a rectangle
                p = pix[y*wid + x];
                // get colour value
                colours = getColour(p);
                // std::cout << "got colours!" << std::endl;

                DrawRect(x, y, 20, 20, colours);
            }
        }
    } 
};


int main(void){
    // prompt user for bitmap dimension until valid
    std::string line;
    int x, y;
    bool onevalue = true;

    while (onevalue || (x==0 || y==0) || (x > 64 || y > 64)){
        std::cout << "Enter Dimension>" << std::endl;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        if (iss >> x >> y) {
            // Successfully parsed both values
            onevalue = false;
        }
        else{
            onevalue = true;
        }
    }

    // create a bitmap of specified dimension
    CharBitmap bitmap;
    bitmap.Create(x, y);
    
    FsOpenWindow(0,0,x*20,y*20,1);
    for(;;)
	{
		FsPollDevice();

		auto key=FsInkey();

        int lb,mb,rb,mx,my;
		FsGetMouseState(lb,mb,rb,mx,my);

        if(FSKEY_ESC==key)
		{
			break;
		}
       switch(key)
		{
        case FSKEY_S:
            std::cout << "here!" << std::endl;
            // save file
            std::ofstream outFile("../bitmap_data.txt");
            outFile << bitmap.wid << " " << bitmap.hei << std::endl;
            for (int y = 0; y < bitmap.hei; y++) {
                for (int x = 0; x < bitmap.wid; x++) {
                    outFile << bitmap.pix[y * bitmap.wid + x];
                    outFile << " ";
                }
                outFile << std::endl;
            }  
            outFile.close();
            break;
        }
        
        if (FSKEY_NULL != key){
            int colourCode = key-FSKEY_0;
            bitmap.SetPixel(mx/20, my/20, '0' + colourCode);   
        }

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        // call draw
        bitmap.Draw();


        // make lattice
        // draw grid lines vertical (white)
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        for (int i=0; i <x; i++){
            glVertex2i(i*20,0);
            glVertex2i(i*20,y*20);
        }
        glEnd();

        // draw grid lines horizontal
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        for (int i=0; i <y; i++){
            glVertex2i(0, i*20);
            glVertex2i(x*20, i*20);
        }
        glEnd();
        FsSwapBuffers();
        FsSleep(25);
    }
    return 0;
}