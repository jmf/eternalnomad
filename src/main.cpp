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
#include <ncurses.h>
#include <unistd.h>
#include "Player.h"
#include "World.h"

using namespace std;

int main (int argc, char** argv){
  int key=-1;
  int collide=0;
  
  initscr();

  if(has_colors()==false)//Check for color support
  {
    endwin();
    cout<<"Sorry, your terminal doesn't support colors."<<endl;
		return -1;
  }
  
  Player plr;
  World wrld;
  
  wrld.genWorld(-1);//Generating world
  plr.loadPlayer("../data/player.sve");//Load player
  timeout(50);//Timeout for keypress

  while(true){

    key = getch();//Keypress search
    collide = wrld.freeWay(plr.playerypos, plr.playerxpos, key);//Check collision

    plr.update(key, collide);//Update player position
    wrld.draw(stdscr,plr.playerxpos);//Draw world
    plr.draw(stdscr);//Draw player
    refresh();
  }

  endwin();
  return 0;
  }

void menu(){
  //Make a menu here...
}


