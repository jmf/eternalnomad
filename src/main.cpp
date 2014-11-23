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
#include "time.h"
#include "Player.h"
#include "World.h"

using namespace std;

int main (int argc, char** argv){

	bool timed=false;
	int key=-1;
	int dir=0;
	int collide=0;
	struct timespec old;
	struct timespec tp;

	Player plr;
	World wrld;
	

	if(argc==1){
		wrld.genWorld(-1);//TODO: Allow player to choose custom seed
	}
	else if(argc==2){
		wrld.loadWorld(argv[1]);
	}
	else{
		cout<<"Bad Arguments!"<<endl;
		cout<<"Try \"./eternalnomad\" or \"./eternalnomad <worldfile>\""<<endl;
		return 1;
	}


	plr.loadPlayer("player.sve");//Load player

	initscr();

	if(has_colors()==false)//Check for color support
	{
		endwin();
		cout<<"Sorry, your terminal doesn't support colors."<<endl;
		return 1;
	}
	timeout(10);//Timeout for keypress

	while(true){
		clock_gettime(CLOCK_MONOTONIC, &old);
		key = getch();//Keypress search

		if(key==100){//Direction of walking
			dir=1;
		}
		else if(key==97){
			dir=-1;
		}
		else if(key==32||key==119){
			dir=2;
		}
		else{
			dir=0;
		}

		collide = wrld.goWay(plr.playerypos, plr.playerxpos,&dir);//Check collision
		plr.update(collide, dir);//Update player position

		flushinp();//Flush input buffer

		wrld.draw(stdscr,plr.playerxpos);//Draw world
		plr.draw(stdscr);//Draw player

		refresh();//Refresh terminal

		while(timed==false){
			clock_gettime(CLOCK_MONOTONIC, &tp);

			if(tp.tv_nsec<=(old.tv_nsec+500000000)){ //0.5 seconds per frame
				timed=false;
			}
			else{
				timed=true;
			}

			if(tp.tv_sec>old.tv_sec){ //If frame took longer than one second
				timed=true;
			}
		}
	timed=false;

	}
	endwin();
	return 0;
}


