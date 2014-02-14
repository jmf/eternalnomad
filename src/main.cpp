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
  bool keypress=false;
  int key=-1;
  
  initscr();

  if(has_colors()==false)//Check for color support
  {
    endwin();
    cout<<"Sorry, your terminal doesn't support colors."<<endl;
		return -1;
  }
  
	Player plr;
  World wrld;
  
  wrld.genWorld(1337);//Generating world, no seed implemented yet
  plr.loadPlayer("../data/player.sve");//Load player
  timeout(100);//Timeout for keypress

  while(true){
    key = getch();//Keypress search
    wrld.draw(stdscr,plr.playerpos);
    plr.draw(stdscr, key);
    refresh();
  }

  endwin();
  return 0;
}

void menu(){
  //Make a menu here...
}


