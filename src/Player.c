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


#include <stdio.h>
#include <ncurses.h>
#include "Player.h"

void loadPlayer(struct Player *p, char* filename){//TODO: Rework for smaller files
  puts("here");
  FILE* fdata =fopen(filename ,"r");
  puts("hore");
  //fgets(p->name, 15, (FILE*)fdata);
  int anim, pic, part;
  puts("hare");
  for(anim=0; anim<4; anim++){
    for(pic=0; pic<4; pic++){
      for(part=0; part<4; part++){

       fgets(p->frame[anim][pic][part], 6, fdata);
       printf("%s\n",p->frame[anim][pic][part]);
      }
    }
  }
  fclose(fdata);
}

void update(struct Player *p, int state, int collide)//TODO: Check if headroom free
{
  p->walkvar++;

  if(state==-1&&p->facedir==0){//Idle right
    p->playerstate=0;
  }

  else if(state==-1&&p->facedir==1){//Idle left
    p->playerstate=1;
  }

  else if(state==100){//RIGHT
    p->playerstate=2;
    p->facedir=0;
  }

  else if(state==97){//LEFT
      p->playerstate=3;
      p->facedir=1;
  }

  else if((state==32||state==119)&&collide!=4){//Jump!
    p->playerypos=p->playerypos-5;
  }

  if(p->playerstate==2&&collide==0){//Free right
    p->playerxpos++; 
  }

  else if(p->playerstate==3&&collide==0){//Free left
    p->playerxpos--;
  }

  else if(p->playerstate==2&&collide==2){//Step right
    p->playerypos--;
    p->playerxpos++;
  }

  else if(p->playerstate==3&&collide==2){//Step left
    p->playerypos--;
    p->playerxpos--;
  }

  else if(collide==3){//Wall in the way and falling
    p->playerypos++;
  }

  if(p->playerstate==2&&collide==4){//falling right
    p->playerypos++;
    p->playerxpos++;
  }

  else if(p->playerstate==3&&collide==4){//falling left
    p->playerypos++;
    p->playerxpos--;
  }
  
  else if(p->playerstate<2&&collide==4){//falling down
    p->playerypos++;
  }
}


void drawPlayer(struct Player *p, WINDOW *win)
{
  
  if(p->walkvar>3)
  {
    p->walkvar=0;
  }

  mvwprintw(win, 12+p->playerypos, 20, "%s", p->frame[p->playerstate][1][p->walkvar]);
  mvwprintw(win, 13+p->playerypos, 20, "%s", p->frame[p->playerstate][1][p->walkvar]);
  mvwprintw(win, 14+p->playerypos, 20, "%s", p->frame[p->playerstate][2][p->walkvar]);
  mvwprintw(win, 15+p->playerypos, 20, "%s", p->frame[p->playerstate][3][p->walkvar]);


}


