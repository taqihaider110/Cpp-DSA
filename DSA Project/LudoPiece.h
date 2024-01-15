#include<iostream>
using namespace std;

#ifndef LUDOPIECE_H
#define LUDOPIECE_H

#include"LudoNode.h"

class Piece {
	public:
		const Node* win;  //place where piece is scored
		Node* start;	//Jail Location
		Node* position; //piece position
		string team;	//color/team of piece
		int relpos=-1;	//distance from starting point
		bool inplay=true;	//Shows that this piece is ready to play (not win)
		bool inJail=true;	//Shows that this piece is INSIDE jail
		bool canmove=true;	//Shows that this piece's turn is valid or not
		
		Piece(string t="",Node* pos=NULL, Node* w=NULL):team(t),position(pos),win(w),start(pos) {}
		
		int getcaptured(){
			(*(position->piececount))--;
			position = start;
			relpos=-1; 
			inJail=true;
			return 3;
		}
		int getpl(){
			return inplay;
		}
		int getpos(){
			return relpos;
		}
		
		int move(int roll) {
			canmove=true;
			if(inplay) {
				if(!inJail) {
					Node* startpos=position;		//starting position for backtrack in case of invalid move
					int startrel = relpos;
					(*(position->piececount))--;
					int steps=0;
					while(steps<roll) {
						if (ExtendedColoredNode* extraNode = dynamic_cast<ExtendedColoredNode*>(position)) {	//checks if split in route (home line)
							if (extraNode->color == team) {
								position=extraNode->home;
								relpos++;		//goes into home line
							}
							else{
								position=position->next;	//else not in home line but next node
								relpos++;
							}
						}
						 else {
							if(position->next != win) {
								position=position->next;	//move normal
								relpos++;
							} else {
								if(roll-steps>1) {
									position=startpos;
									relpos=startrel;
									(*(position->piececount))++;
									canmove=false;		//if invalid then rollback move
									return 3;
								} else {
									position=position->next;
									relpos++;
									(*(position->piececount))++;
									inplay=false;		//if just enough then declare piece as scored
									canmove=false;
									return 1;
								}
							}
						}
						steps++;
					}
					(*(position->piececount))++;
					return 1;
				} else {
					if(roll==6) {
						position=position->next;		//free from jail
						relpos++;
						inJail=false;
						(*(position->piececount))++;
						return 2;
					} else {
						return 0;
					}
				}
			} else {
				cout<<"This Piece is not In Play, Choose Another Piece."<<endl;   //tried to select piece already scored
				return 0;
			}
		}

};

#endif