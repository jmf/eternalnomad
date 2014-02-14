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
#include "World.h"

using namespace std;

void World::loadWorld(std::string filename){
  fstream fdata;
  fdata.open(filename.c_str());
  //TODO: Insert useful code
	fdata.close();
}

void World::genWorld(int seed){//TODO: Add code that does something
  for(int x=0; x<80; x++){
    for(int y=0; y<50; y++){
      if(y>15){
        World::worldarray[y][x]=1;
      }
      else{
        World::worldarray[y][x]=2;
      }
    }
  }
}


void World::draw(WINDOW *win)
{
  string temp;
	for(int x=0; x<80; x++){
    for(int y=0; y<50;y++){
      if(World::worldarray[y][x]==1){
        temp="#";
      }
			else if(World::worldarray[y][x]==2){
        temp="~";
      }
      else{
        temp=" ";
      }
      mvwprintw(win, y, x, "%s", temp.c_str());
    }
  }
}


