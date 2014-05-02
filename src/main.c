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
#include <unistd.h>
#include "Player.h"
#include "World.h"

int main (int argc, char** argv){
  clock_t timer;
  int key=-1;
  int collide=0;

  initscr();

  if(has_colors()==false)//Check for color support
  {
    endwin();
    printf("Sorry, your terminal doesn't support colors.\n");
    return -1;
  }

  struct Player plr;
  struct World wrld;

  genWorld(&wrld, -1);//Generating world
  loadPlayer(&plr, "../data/player.sve");//Load player


  timeout(10);//Timeout for keypress

  while(true){
    timer=clock();

    //drawWorld(wrld, stdscr,plr.playerxpos);//Draw world
    drawPlayer(&plr, stdscr);//Draw player

    refresh();//Refresh terminal

    key = getch();//Keypress search

    //collide = freeWay(wrld, plr.playerypos, plr.playerxpos, key);//Check collision
    update(&plr, key, collide);//Update player position

    flushinp();//Flush input buffer

    while(clock()-timer<30000){
      nanosleep(10);
    }
  }

  endwin();

  return 0;
}

