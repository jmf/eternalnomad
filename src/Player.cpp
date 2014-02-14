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
  
  for(int anim=0; anim<4; anim++){
    for(int pic=0; pic<4; pic++){
      for(int part=0; part<4; part++){
        getline(fdata, Player::frame[anim][part][pic]);
      }
    }
  }
	fdata.close();
}


void Player::draw(WINDOW *win, int state)//TODO: Implement jumping
{
  if(Player::walkvar>3)
  {
    Player::walkvar=0;
  }
  if(state==-1&&Player::facedir==0){//Idle right
    Player::playerstate=0;
  }
  else if(state==-1&&Player::facedir==1){//Idle left
    Player::playerstate=1;
  }
  else if(state==100){//RIGHT
    Player::playerstate=2;
    Player::facedir=0;
  }
  else if(state==97){//LEFT
    Player::playerstate=3;
    Player::facedir=1;
  }
  else{
    //ERROR
  }

  mvwprintw(win, 12, 20, "%s", (Player::frame[Player::playerstate][0][Player::walkvar]).c_str());
  mvwprintw(win, 13, 20, "%s", (Player::frame[Player::playerstate][1][Player::walkvar]).c_str());
  mvwprintw(win, 14, 20, "%s", (Player::frame[Player::playerstate][2][Player::walkvar]).c_str());
  mvwprintw(win, 15, 20, "%s", (Player::frame[Player::playerstate][3][Player::walkvar]).c_str());

  if(clock()-Player::timer>5000){
    Player::walkvar++;
    Player::timer=clock();

    if(Player::playerstate==2){
      Player::playerpos++;
    }

    else if(Player::playerstate==3){
      Player::playerpos--;
    }

  }
}


