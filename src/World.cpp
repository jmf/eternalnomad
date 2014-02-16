/*
* Copyright (C) 2014 jmf
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
* NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <stdlib.h>
#include "World.h"

using namespace std;

void World::loadWorld(std::string filename){
  fstream fdata;
  fdata.open(filename.c_str());
  //TODO: Insert useful code
	fdata.close();
}

void World::genWorld(int seed){//TODO: Add better generator
  if(seed==-1){
    srand(clock()%1337);
  }
  else{
    srand(seed);
  }
  for(int x=0; x<2000; x++){
    for(int y=0; y<50; y++){
      if(y>15){
        World::worldarray[y][x]=rand()%2;
      }
      else{
        World::worldarray[y][x]=-1;
      }

      World::worldarray[15][35]=2;
      World::worldarray[14][36]=2;
      World::worldarray[13][37]=2;
      World::worldarray[12][38]=2;
      World::worldarray[11][39]=2;
      World::worldarray[10][40]=2;
      World::worldarray[10][41]=2;
      World::worldarray[10][42]=2;
      World::worldarray[10][43]=2;
      World::worldarray[10][44]=2;
      World::worldarray[11][45]=2;
      World::worldarray[12][46]=2;
      World::worldarray[13][47]=2;
      World::worldarray[14][48]=2;
      World::worldarray[15][49]=2;
      
      World::worldarray[16][21]=2;
      World::worldarray[16][24]=2;
     
    }
  }
}

void World::draw(WINDOW *win, int pos)
{
  string temp;
	for(int x=pos; (x-pos)<80; x++){
    for(int y=0; y<50;y++){
      if(World::worldarray[y][x]==1){
        temp="#";
      }
      else if(World::worldarray[y][x]==2)
      {
        temp="@";
      }
      else if(World::worldarray[y][x]==-1){
        temp=" ";
      }
      else{
        temp="*";
      }
      mvwprintw(win, y, x-pos, "%s", temp.c_str());
    }
  }
}

int World::freeWay(int y, int x, int state){
  World::wall=0;
  World::pit=1;

	if(state==100){//RIGHT
    for(int i=0; i<4; i++){
      if(World::worldarray[y+12+i][x+25]!=-1){
        World::wall=1;
      }
    }
     
    if((World::worldarray[y+15][x+25]!=-1)&&(World::worldarray[y+10][x+25]==-1)){
      World::wall=2;
    }

    for (int i=0; i<5; i++){//Falling right!
	    if(World::worldarray[y+16][x+21+i]!=-1){
        World::pit=0;
      }   
    }
	}

  else if(state==97){//LEFT
    for(int i=0; i<4; i++){
      if(World::worldarray[y+12+i][x+19]!=-1){
        World::wall=1;
      }
    }
    
    if((World::worldarray[y+15][x+19]!=-1)&&(World::worldarray[y+10][x+19]==-1)){
      World::wall=2;
    }

		for (int i=0; i<5; i++){//Falling left!
	    if(World::worldarray[y+16][x+19+i]!=-1){
        World::pit=0;
      }   
    }
  }   
    

	if(World::pit==0&&World::wall==0){
    return 0;
  }

	else if(World::pit==0&&World::wall==1){
    return 1;
  }

	else if(World::pit==0&&World::wall==2){
    return 2;
  }

	else if(World::pit==1&&World::wall==1){
    return 3;
  }

  else if(World::pit==1&&World::wall==0){
    return 4;
  }
}












