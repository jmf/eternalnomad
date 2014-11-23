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
FREE=0,
STEP=1,
PIT=2,
JUMP=3
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
			seed=Str2Int(mapdata);
		}

		genWorld(seed);
	
		while(!fdata.eof()){
			pos="";
			xpos="";
			ypos="";
			mapdata="";
			
			getline(fdata, mapdata);
			if(mapdata!=""){
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
						worldarray[Str2Int(y)][Str2Int(x)]=Str2Int(material);
					}
				}
			}
		}
	}
	else{
		genWorld(-1);
	}

	fdata.close();
}


void World::genWorld(int seed){//TODO: Add better generator
	if(seed==-1){
		seed=clock()%1337;
	}
	else{
		seed=seed;
	}
	srand(seed);

	for(int x=0; x<2000; x++){
		for(int y=0; y<50; y++){
			if(y>15){
				worldarray[y][x]=rand()%2;
			}
			else{
				worldarray[y][x]=AIR;
			}
		}
	}
}


void World::draw(WINDOW *win, int pos){
	string temp;
	for(int x=pos; (x-pos)<80; x++){
		for(int y=0; y<50;y++){
			if(worldarray[y][x]==HASH){
				temp="#";
			}
			else if(worldarray[y][x]==CONCRETE)
			{
				temp="@";
			}
			else if(worldarray[y][x]==AIR){
				temp=" ";
			}
			else{
				temp="*";
			}
			mvwprintw(win, y, x-pos, "%s", temp.c_str());
		}
	}
}


int World::goWay(int y, int x, int* dir){
	
	int direction=*dir;
	int step=0;
	int pit=1;
	int jump=0;
	int headfree=0;
	int row=0;

	if(direction==2){
		direction=0;
		jump=1;
	}


	for(int i=0; i<3; i++){//Check for wall
		if(direction==1){
			if(worldarray[y+12+i][x+24]!=AIR){
				direction=0;
			}
		}
		else if(direction==-1){
			if(worldarray[y+12+i][x+19]!=AIR){
				direction=0;
			}
		}
	}

	for(int i=0; i<4; i++){//check for pit
		if(direction==1){
			if(worldarray[y+16][x+21+i] != AIR){
				pit=0;
			}
		}
		else if(direction==-1){
			if(worldarray[y+16][x+19+i] != AIR){
				pit=0;
			}
		}
		else if(direction==0){
			if(worldarray[y+16][x+20+i] != AIR){
				pit=0;
			}
		}
	}

	if(direction==1){//Step right?
		if(worldarray[y+15][x+24]!=AIR){
			for(int i=0; i<3; i++){
				if(worldarray[y+11+i][x+24]==AIR){
					step=1;
				}
				else{
					step=0;
					break;
				}
			}
		}
	}
	else if(direction==-1){//Step left?
		if(worldarray[y+15][x+19]!=AIR){
			for(int i=0; i<4; i++){
				if(worldarray[y+11+i][x+20]==AIR){
					step=1;
				}
				else{
					step=0;
					break;
				}
			}
		}
	}

	if(jump==1 && pit==0){//check for headroom to jump
		direction=2;

		for(int h=0; h<6; h++){
			row=0;
			for(int w=0; w<4; w++){
				if(worldarray[y+11-h][x+20+w]==AIR){
					row++;
				}
			}
			if(row==4){
				direction++;
			}
			else{
				*dir = direction;
				return JUMP;
			}
		}
	}
	else if(jump==1 && pit==1){
		direction=0;
	}

	if(step==1){
		return STEP;
	}

	*dir=direction;//Only when wall might be in the way or jumping

	if(pit==0 && jump==1){
		return JUMP;
	}

	if(pit==0 && step==0){
		return FREE;
	}

	if(pit==1){
		return PIT;
	}
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

