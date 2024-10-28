#include <iostream>
#include <math.h>
#include "fssimplewindow.h"
#include "equation.h"

// int main(void)
// {
// 	double a,b,c,d,e,f,x,y,D;

// 	std::cout << "ax+by=c\n";
// 	std::cout << "dx+ey=f\n";
// 	std::cout << "Enter a b c d e f:";

// 	std::cin >> a >> b >> c >> d >> e >> f;

// 	D=a*e-b*d;
// 	if(fabs(D)<tolerance)
// 	{
// 		std::cout << "No solution.\n";
// 	}
// 	else
// 	{
// 		x=(e*c-b*f)/D;
// 		y=(a*f-c*d)/D;
// 		std::cout << "x=" << x << " y=" << y << '\n';
// 	}
// 	return 0;
// }

int main(void)
{
	SimultaneousEquation eqn;
	Axes axes;

	double x,y;
	double a,b,c,d,e,f;
	std::cout << "ax+by=c\n";
	std::cout << "dx+ey=f\n";
	std::cout << "Enter a b c d e f:";
	
	// Input coefficients
    std::cin >>
	eqn.eqn[0].a >> eqn.eqn[0].b >> eqn.eqn[0].c >>
	eqn.eqn[1].a >> eqn.eqn[1].b >> eqn.eqn[1].c;


	if(true==eqn.Solve(x,y))
	{
		std::cout << "x=" << x << " y=" << y << "\n";
	}
	else
	{
		std::cout << "No solution.\n";
	}

	FsOpenWindow(0,0,600,600,1);
	for(;;)
	{
		FsPollDevice();
		if(FSKEY_ESC==FsInkey())
		{
			break;
		}
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		axes.Draw();
		eqn.Plot();
		FsSwapBuffers();
	}
	return 0;
}