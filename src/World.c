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

#include <ncurses.h>
#include <stdlib.h>
#include "World.h"

void loadWorld(struct World *w, char* filename){
  //TODO: Implement loading world
}

void genWorld(struct World* w, int seed){//TODO: Add better generator

  int x, y;
  if(seed==-1){
    srand(clock()%1337);
  }
  else{
    srand(seed);
  }
  for(x=0; x<2000; x++){
    for(y=0; y<50; y++){
      if(y>15){
        w->worldarray[y][x]=rand()%2;
      }
      else{
        w->worldarray[y][x]=-1;
      }

      w->worldarray[15][35]=2;
      w->worldarray[14][36]=2;
      w->worldarray[13][37]=2;
      w->worldarray[12][38]=2;
      w->worldarray[11][39]=2;
      w->worldarray[10][40]=2;
      w->worldarray[10][41]=2;
      w->worldarray[10][42]=2;
      w->worldarray[10][43]=2;
      w->worldarray[10][44]=2;
      w->worldarray[11][45]=2;
      w->worldarray[12][46]=2;
      w->worldarray[13][47]=2;
      w->worldarray[14][48]=2;
      w->worldarray[15][49]=2;

      w->worldarray[11][60]=2;
      w->worldarray[12][60]=2;
      w->worldarray[13][60]=2;
      w->worldarray[14][60]=2;
      w->worldarray[15][60]=2;

    }
  }
}

void drawWorld(struct World *w, WINDOW *win, int pos)
{
  int x=0;
  int y=0;
  char temp;
	for(x=pos; (x-pos)<80; x++){
    for(y=0; y<50;y++){
      if(w->worldarray[y][x]==1){
        temp='#';
      }
      else if(w->worldarray[y][x]==2)
      {
        temp='@';
      }
      else if(w->worldarray[y][x]==-1){
        temp=' ';
      }
      else{
        temp='*';
      }
      mvwprintw(win, y, x-pos, "%s", temp);
    }
  }
}

int freeWay(struct World *w, int y, int x, int state){//TODO:Check for headroom
  w->wall=0;
  w->pit=1;
  int i;
	if(state==100){//RIGHT
    for(i=0; i<3; i++){
      if(w->worldarray[y+12+i][x+25]!=-1){
        w->wall=1;
      }
    }
     
    if((w->wall!=1)&&(w->worldarray[y+15][x+25]!=-1)&&(w->worldarray[y+11][x+25]==-1)){
      w->wall=2;
    }

    for (i=0; i<5; i++){//Falling right!
	    if(w->worldarray[y+16][x+21+i]!=-1){
        w->pit=0;
      }   
    }
	}

  else if(state==97){//LEFT
    for(i=0; i<3; i++){
      if(w->worldarray[y+12+i][x+19]!=-1){
        w->wall=1;
      }
    }
    
    if((w->wall!=1)&&(w->worldarray[y+15][x+19]!=-1)&&(w->worldarray[y+11][x+19]==-1)){
      w->wall=2;
    }

		for (i=0; i<5; i++){//Falling left!
	    if(w->worldarray[y+16][x+19+i]!=-1){
        w->pit=0;
      }   
    }
  }   

  else{
    for (i=0; i<6; i++){//Falling down!
	    if(w->worldarray[y+16][x+19+i]!=-1){
        w->pit=0;
      }   
    }
  }

	if(w->pit==0&&w->wall==0){
    return 0;
  }

	else if(w->pit==0&&w->wall==1){
    return 1;
  }

	else if(w->pit==0&&w->wall==2){
    return 2;
  }

	else if(w->pit==1&&w->wall==1){
    return 3;
  }

  else if(w->pit==1&&w->wall==0){
    return 4;
  }
}

