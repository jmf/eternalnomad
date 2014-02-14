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
#include "Player.h"

using namespace std;

void Player::loadPlayer(std::string filename){//TODO: Rework for smaller files
  fstream fdata;
  fdata.open(filename.c_str());
  getline(fdata, Player::name);
  
  for(int anim=0; anim<2; anim++){
    for(int pic=0; pic<4; pic++){
      for(int part=0; part<4; part++){
        getline(fdata, Player::frame[anim][part][pic]);
      }
    }
  }
	fdata.close();
}


void Player::draw(WINDOW *win, int state)//TODO: Make walking animation time-based (time.h)
{
  if(Player::walkvar>3)
  {
    Player::walkvar=0;
  }
  if(state==-1){//idle
    mvwprintw(win, 12, 20, "%s", (Player::frame[0][0][walkvar]).c_str());
    mvwprintw(win, 13, 20, "%s", (Player::frame[0][1][walkvar]).c_str());
    mvwprintw(win, 14, 20, "%s", (Player::frame[0][2][walkvar]).c_str());
    mvwprintw(win, 15, 20, "%s", (Player::frame[0][3][walkvar]).c_str());
  }
  else{//walk
    mvwprintw(win, 12, 20, "%s", (Player::frame[1][0][walkvar]).c_str());
    mvwprintw(win, 13, 20, "%s", (Player::frame[1][1][walkvar]).c_str());
    mvwprintw(win, 14, 20, "%s", (Player::frame[1][2][walkvar]).c_str());
    mvwprintw(win, 15, 20, "%s", (Player::frame[1][3][walkvar]).c_str());
  }
  Player::walkvar++;
}


