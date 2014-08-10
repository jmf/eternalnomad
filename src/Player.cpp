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

using namespace std;

void Player::loadPlayer(std::string filename){//TODO: Rework for smaller files
  fstream fdata;
  fdata.open(("../data/"+filename).c_str());
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

void Player::update(int collide)//TODO: Make falling a bit more flowing
{
  if(collide<5){
    Player::playerstate=2;
  }
  else if(collide<10){
    Player::playerstate=3;
  }

  if(collide==R_FREE){
    Player::playerxpos++;
    Player::walkvar++;
  }
  else if(collide==R_STEP){
    Player::playerxpos++;
    Player::playerypos--;
    Player::walkvar++;
  }
  else if(collide==R_WALL){
  }
  else if(collide==R_WALLPIT){
    Player::playerypos++;
  }
  else if(collide==R_PIT){
    Player::playerxpos++;
    Player::playerypos++;
    Player::walkvar++;
  }


  else if(collide==L_FREE){
    Player::playerxpos--;
    Player::walkvar++;
  }
  else if(collide==L_STEP){
    Player::playerxpos--;
    Player::playerypos--;
    Player::walkvar++;
  }
  else if(collide==L_WALL){
    
  }
  else if(collide==L_WALLPIT){
    Player::playerypos++;
  }
  else if(collide==L_PIT){
    Player::playerxpos--;
    Player::playerypos++;
    Player::walkvar++;
  }

  else if(collide==JUMP){
    playerypos=playerypos-5;
  }

  else if(collide==IDLE || collide==FALL){
    if(Player::playerstate==2){
      Player::playerstate=0;
    }
    else if(Player::playerstate==3){
      Player::playerstate=1;
    }

    if(collide==FALL){
      Player::playerypos++;
    }
    Player::walkvar++;
  }

}


void Player::draw(WINDOW *win)
{
  
  if(Player::walkvar>3)
  {
    Player::walkvar=0;
  }

  mvwprintw(win, 12+Player::playerypos, 20, "%s", (Player::frame[Player::playerstate][0][Player::walkvar]).c_str());
  mvwprintw(win, 13+Player::playerypos, 20, "%s", (Player::frame[Player::playerstate][1][Player::walkvar]).c_str());
  mvwprintw(win, 14+Player::playerypos, 20, "%s", (Player::frame[Player::playerstate][2][Player::walkvar]).c_str());
  mvwprintw(win, 15+Player::playerypos, 20, "%s", (Player::frame[Player::playerstate][3][Player::walkvar]).c_str());

}


