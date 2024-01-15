#include<iostream>
#include<conio.h>
using namespace std;

#ifndef LUDOPLAYER_H
#define LUDOPLAYER_H

#include"LudoPiece.h"
#include"validate.h"

class Player {
		string Name;
		bool playing=true; //if player has won or not (still playing)
		bool trapped=true; //if player has any valid moves for the turn
		bool isComp=false; //If player is AI controlled
	public:
		Piece* pieces[4]; //each player's 4 pieces
		Player() {
			getline(cin,Name);
			char input;
			while(input!='Y'&&input!='y'&&input!='N'&&input!='n') {
				cout<<"Is "<<Name<<" Computer Controlled? [Y/N]"<<endl;		//initializes name and whether AI controlled
				cin>>input;
				switch(input) {
					case 'Y':
					case 'y':
						isComp=true;
						break;
					case 'N':
					case 'n':
						isComp=false;
						break;
					default:
						cout<<"Invalid Input, Give Y(yes) or N(no) as answer.\n";
				}
				fflush(stdin);
				cin.clear();
			}
		}
		string getname() {
			return Name;
		}
		bool playstate() {
			return playing;
		}

		void checktrapped() {
			if((pieces[0]->inJail||!(pieces[0]->canmove))&&(pieces[1]->inJail|!(pieces[1]->canmove))&&(pieces[2]->inJail||!(pieces[2]->canmove))&&(pieces[3]->inJail||!(pieces[3]->canmove))) {
				trapped=true;  //checks if no valid moves.
			}
		}

		void checkplay() {
			if(pieces[0]->inplay == false && pieces[1]->inplay == false && pieces[2]->inplay == false && pieces[3]->inplay == false ) {
				playing=false;	///checks if player has won
				return;	
			}
		}
		int turn(int &z) { //turn logic
			if(playing) {
				int x;
				int roll;
				int pieceno;
				cout<<"\n---"<<Name;
				if(isComp) {
					cout<<" [AI]";
				}
				cout<<"'s Turn---\n";		//outputs
				if(!isComp) {
					cout<<"Press any key to roll..."<<endl;
					getch();
				}
				roll = rand()%6+1;
				if(isComp) {
					cout<<Name<<" rolled a "<<roll<<"!"<<endl;
				}
				do {
					if(!isComp) {
						cout<<Name<<" rolled a "<<roll<<"!"<<endl;
					}
					if(trapped && roll!=6) {
						cout<<"No Valid Moves, Turn Skipped!"<<endl<<endl;
						return -1;
					}
					if(!isComp) {
						cout<<"Choose which piece to attempt to move:"<<endl;
						for(int i=0; i<4; i++) {
							if(pieces[i]->getpl()) {
								cout<<"Piece #"<<i<<" currently ";			//outputs location of pieces
								if(pieces[i]->relpos==-1) {
									cout<<"in jail"<<endl;  //output
								} else {
									cout<<pieces[i]->relpos<<" steps from Start Position."<<endl;
								}
							}
						}
						cout<<endl;
						pieceno = InputValid<int>();
						while(pieceno<0||pieceno>3) {
							cout<<"Incorrect Piece Number, Try Another Integer."<<endl;
							pieceno = InputValid<int>();
						}
					} else {
						do {
							pieceno=rand()%4;
						} while(!(pieces[pieceno]->canmove)); 	
					}
					z = pieceno;  //changes current piece in LudoGame by reference
					x = pieces[pieceno]->move(roll);	//moves piece
					if(x==2) {
						trapped=false;
					}
					checktrapped();		//updation based on return from move()
					if(x==0 && !isComp) {
						cout<<"\n\nInvalid Move (Roll not high enough to Free a Piece).\nPlease Choose Another Piece."<<endl;
					}
					if(x==3 && !isComp) {
						cout<<"\n\nInvalid Move (More moves than needed to Score a Piece).\nPlease Choose Another Piece."<<endl;
					}
				} while(x == 0 || x==3 || trapped);
				checkplay();	//checks if player won after turn
				return x;
			} else {
				return -1;
			}
		}

};

#endif