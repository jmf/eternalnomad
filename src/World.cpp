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

enum collision{
R_FREE=0,
R_STEP=1,
R_WALL=2,
R_WALLPIT=3,
R_PIT=4,

L_FREE=5,
L_STEP=6,
L_WALL=7,
L_WALLPIT=8,
L_PIT=9,

JUMP=10,
FALL=11,
IDLE=12
};

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
     
      World::worldarray[11][60]=2;
      World::worldarray[12][60]=2;
      World::worldarray[13][60]=2;
      World::worldarray[14][60]=2;
      World::worldarray[15][60]=2;

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


int World::goWay(int y, int x, int state){//TODO:Check for headroom
  World::wall=0;
  World::pit=1;
  World::step=0;

	if(state==100){//RIGHT

    for (int i=0; i<6; i++){//Falling down!
	    if(World::worldarray[y+16][x+21+i]!=-1){
        World::pit=0;
      }   
    }

    for(int i=0; i<3; i++){//Check for wall
      if(World::worldarray[y+12+i][x+24]!=-1){
        World::wall=1;
      }
    }

    if((World::wall!=1)&&(World::worldarray[y+15][x+24]!=-1)&&(World::worldarray[y+11][x+24]==-1)){//Check for step
      World::step=1;
    }

    if(World::step==1){
      return R_STEP;
    }

    if(World::wall==1 && World::pit==0){
      return R_WALL;
    }

    else if(World::wall==1 && World::pit==1){
      return R_WALLPIT;
    }

    else if(World::wall==0 && World::pit==1){
      return R_PIT;
    }
    else{
      return R_FREE;
    }
   
  }


  else if(state==97){//LEFT

    for (int i=0; i<6; i++){//Falling down!
	    if(World::worldarray[y+16][x+17+i]!=-1){
        World::pit=0;
      }   
    }

    for(int i=0; i<3; i++){
      if(World::worldarray[y+12+i][x+19]!=-1){
        World::wall=1;
      }
    }
  
    if((World::wall!=1)&&(World::worldarray[y+15][x+19]!=-1)&&(World::worldarray[y+11][x+19]==-1)){//Check for step
      World::step=1;
    }  
  
    if(World::step==1){
      return L_STEP;
    }

    if(World::wall==1 && World::pit==0){
      return L_WALL;
    }

    else if(World::wall==1 && World::pit==1){
      return L_WALLPIT;
    }

    else if(World::wall==0 && World::pit==1){
      return L_PIT;
    }
    else{
      return L_FREE;
    }
  }

  else if(state==32||state==119){
    for (int i=0; i<6; i++){//Falling down!
	    if(World::worldarray[y+16][x+20+i]!=-1){
        World::pit=0;
      }   
    }

    if(World::pit==0){
      return JUMP;
    }
    else{
      return FALL;
    }
  }

  else{
    for (int i=0; i<4; i++){//Falling down!
	    if(World::worldarray[y+16][x+20+i]!=-1){
        World::pit=0;
      }   
    }
    if(World::pit!=0){
      return FALL;
    }
    else{
      return IDLE;
    }
  }
  return IDLE;
}


