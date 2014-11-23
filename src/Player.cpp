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
FREE=0,
STEP=1,
PIT=2,
JUMP=3
};


using namespace std;

void Player::loadPlayer(std::string filename){//TODO: Rework for smaller files
	fstream fdata;
	fdata.open(("../data/"+filename).c_str());
	getline(fdata, name);
	
	for(int anim=0; anim<4; anim++){
		for(int pic=0; pic<4; pic++){
			for(int part=0; part<4; part++){
				getline(fdata, frame[anim][part][pic]);
			}
		}
	}
	fdata.close();
}

void Player::update(int collide, int dir)
{
	//PLAYERSTATE: 0 rightface, 1 leftface, 2 rightgo, 3 leftgo

	int headroom=0;


	if(dir>=2){
		headroom=dir-2;
		dir=0;	
	}
	else if(dir==1){
		playerstate=2;
	}
	else if(dir==-1){
		playerstate=3;
	}
	else if(dir==0){
		if(playerstate==2){
			playerstate=0;
		}
		else if(playerstate==3){
			playerstate=1;
		}
	}


	playerxpos=playerxpos+dir; //Player direction

	if(collide==FREE){
		walkvar++;
	}
	
	else if(collide==STEP){
		playerypos--;
		walkvar++;
	}

	else if(collide==PIT){
		playerypos++;
		walkvar++;
	}

	else if(collide==JUMP){
		playerypos=playerypos-headroom;
	}
}

void Player::draw(WINDOW *win)
{
	
	if(walkvar>3)
	{
		walkvar=0;
	}

	mvwprintw(win, 12+playerypos, 20, "%s", (frame[playerstate][0][walkvar]).c_str());
	mvwprintw(win, 13+playerypos, 20, "%s", (frame[playerstate][1][walkvar]).c_str());
	mvwprintw(win, 14+playerypos, 20, "%s", (frame[playerstate][2][walkvar]).c_str());
	mvwprintw(win, 15+playerypos, 20, "%s", (frame[playerstate][3][walkvar]).c_str());

}


