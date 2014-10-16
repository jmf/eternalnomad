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
#include <stdlib.h>
#include "World.h"

using namespace std;

enum mats{
HASH=0,
CONCRETE=2,
AIR=10
};

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

void World::loadWorld(std::string filename){//TODO: Throw an error or give error message when world not loadable || TODO: x:y instead of y:x
	int strpos;
	string mapdata;
	string material; //Used material
	string pos; //x:y
	string xpos; //x position of material
	string ypos; //y position of material
	fstream fdata;
	fdata.open(("../data/"+filename).c_str());
	if(fdata.is_open()){//Does file work?

		if(!fdata.eof()){
			getline(fdata, mapdata);
			World::seed=Str2Int(mapdata);
		}

		World::genWorld(World::seed);
	
		while(!fdata.eof()){
			pos="";
			xpos="";
			ypos="";
			mapdata="";
	
			getline(fdata, mapdata);
			//Split material:x:y into material and y:x
			strpos=mapdata.find(":");
			string material=mapdata.substr(0, strpos);
			string pos=mapdata.substr(strpos+1, 50);
			//Split y:x into x and y
			strpos=pos.find(":");
			string y=pos.substr(0, strpos);
			string x=pos.substr(strpos+1,50);
			//Apply to map:
			if( (material!="") && (x!="") && (y!="") ){
				if((Str2Int(x)>0) && (Str2Int(x)<2001) && (Str2Int(y)>0) && (Str2Int(y)<51)){
					World::worldarray[Str2Int(y)][Str2Int(x)]=Str2Int(material);
				}
			}
		}
	}
	else{
		World::genWorld(-1);
	}

	fdata.close();
}


void World::genWorld(int seed){//TODO: Add better generator
	if(seed==-1){
		World::seed=clock()%1337;
	}
	else{
		World::seed=seed;
	}
	srand(World::seed);

	for(int x=0; x<2000; x++){
		for(int y=0; y<50; y++){
			if(y>15){
				World::worldarray[y][x]=rand()%2;
			}
			else{
				World::worldarray[y][x]=AIR;
			}
		}
	}
}


void World::draw(WINDOW *win, int pos){
	string temp;
	for(int x=pos; (x-pos)<80; x++){
		for(int y=0; y<50;y++){
			if(World::worldarray[y][x]==HASH){
				temp="#";
			}
			else if(World::worldarray[y][x]==CONCRETE)
			{
				temp="@";
			}
			else if(World::worldarray[y][x]==AIR){
				temp=" ";
			}
			else{
				temp="*";
			}
			mvwprintw(win, y, x-pos, "%s", temp.c_str());
		}
	}
}


int World::goWay(int y, int x, int state){//TODO:Check for headroom
	World::wall=0;
	World::pit=1;
	World::step=0;

	if(state==100){//RIGHT

		for (int i=0; i<6; i++){//Falling down!
			if(World::worldarray[y+16][x+21+i]!=AIR){
				World::pit=0;
			}
		}

		for(int i=0; i<3; i++){//Check for wall
			if(World::worldarray[y+12+i][x+24]!=AIR){
				World::wall=1;
			}
		}

		if((World::wall!=1)&&(World::worldarray[y+15][x+24]!=AIR)&&(World::worldarray[y+11][x+24]==AIR)){//Check for step
			World::step=1;
		}

		if(World::step==1){
			return R_STEP;
		}

		if(World::wall==1 && World::pit==0){
			return R_WALL;
		}

		else if(World::wall==1 && World::pit==1){
			return R_WALLPIT;
		}

		else if(World::wall==0 && World::pit==1){
			return R_PIT;
		}
		else{
			return R_FREE;
		}
	 
	}


	else if(state==97){//LEFT

		for (int i=0; i<6; i++){//Falling down!
			if(World::worldarray[y+16][x+17+i]!=AIR){
				World::pit=0;
			}	 
		}

		for(int i=0; i<3; i++){
			if(World::worldarray[y+12+i][x+19]!=AIR){
				World::wall=1;
			}
		}
	
		if((World::wall!=1)&&(World::worldarray[y+15][x+19]!=AIR)&&(World::worldarray[y+11][x+19]==AIR)){//Check for step
			World::step=1;
		}	
	
		if(World::step==1){
			return L_STEP;
		}

		if(World::wall==1 && World::pit==0){
			return L_WALL;
		}

		else if(World::wall==1 && World::pit==1){
			return L_WALLPIT;
		}

		else if(World::wall==0 && World::pit==1){
			return L_PIT;
		}
		else{
			return L_FREE;
		}
	}

	else if(state==32||state==119){
		for (int i=0; i<6; i++){//Falling down!
			if(World::worldarray[y+16][x+20+i]!=AIR){
				World::pit=0;
			}	 
		}

		if(World::pit==0){
			return JUMP;
		}
		else{
			return FALL;
		}
	}

	else{
		for (int i=0; i<4; i++){//Falling down!
			if(World::worldarray[y+16][x+20+i]!=AIR){
				World::pit=0;
			}	 
		}
		if(World::pit!=0){
			return FALL;
		}
		else{
			return IDLE;
		}
	}
	return IDLE;
}

int World::Str2Int(string input){//TODO: Make it less hacky
	int multiplicator=1;
	int output=0;
	for(int n=input.size()-1; n>=0; n--){
		output=output+(input[n]-48)*multiplicator;
		multiplicator=multiplicator*10;
	}
	return output;
}

