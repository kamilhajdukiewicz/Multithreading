//============================================================================
// Name        : lab3_wspolbiezne.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <thread>
#include <math.h>

using namespace std;

constexpr int levelMax = 8;
constexpr int n = 1024;
constexpr int MaxColorCoponentValue = 255;

static int tab[1024][1024];
int color[1024][1024][3];

void fun(int level, int x, int y)
{
	thread watek[3];
	int size = n / pow(2,level);

	for(int i=0;i<size;i++)
	{
		tab[x][y+i]=1;
		tab[x+i][y+size-i]=1;
		tab[x+1][y+1]=1;
	}

	if(level+1<levelMax)
	{
		watek[0] = thread(fun, level+1, x, y );
		watek[1] = thread(fun, level+1, x, y + size/2);
		watek[2] = thread(fun, level+1, x + size/2, y+size/2);

		watek[0].join();
		watek[1].join();
		watek[2].join();
	}

}

int main() {

	int x=0;
	int y=0;
	int i,j;
 	FILE * fp;
	char *filename="new1.ppm";
	char *comment="# ";

	fun(0,0,0);

	for(i=0;i<1024;i++)
		for(j=0;j<1024;j++)
		{
			color[i][j][0]=tab[i][j]*255;
			color[i][j][1]=tab[i][j]*255;
			color[i][j][2]=tab[i][j]*255;
		}

    fp= fopen(filename,"wb");
    fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,n,n,MaxColorCoponentValue);

    fwrite(tab,1,1024*1024,fp);
	return 0;
}
