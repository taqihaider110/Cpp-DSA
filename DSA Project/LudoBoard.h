#include<iostream>
using namespace std;

#ifndef LUDOBOARD_H
#define LUDOBOARD_H

#include <windows.h>
#include "LudoNode.h"
#define RED 79
#define GREEN 160
#define BLUE 31
#define PURPLE 95
#define WHITE 240
#define CYAN 176

// Definition of the Board class
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
class Board {
	private:
		const string colors[4] = {"red", "green", "purple", "blue"};
		int* places[72];
		Node* colorstart[4];
		Node* lines[4]; //only useful for prints
		Node* head;
	public:
		Node* win;
		Node* colorjails[4];

		// Constructor to initialize the circular linked list
		Board() : head(NULL), win(NULL) {
			// Create the circular linked list with the specified pattern
			createBoard();
		}

		// Function to create the circular linked list with the specified pattern
		void createBoard() {


			for(int z=0; z<72; z++) {
				places[z]=new int;
			}
			colorjails[0] = new Node(false);
			*(colorjails[0]->piececount)=4;
			colorjails[1] = new Node(false);
			*(colorjails[1]->piececount)=4;
			colorjails[2] = new Node(false);
			*(colorjails[2]->piececount)=4;
			colorjails[3] = new Node(false);
			*(colorjails[3]->piececount)=4;
			int p=71,count=0;

			win = new Node(false);
			Node *current = win, *curr_line = NULL;

			// Add independent singly linked lists with colors


			for (int j = 0; j < 4; ++j) { // Repeat the pattern 4 times
				lines[(j+1)%4] = curr_line = new ColoredNode(colors[(j+1)%4], false);
				places[p--]=curr_line->piececount;
				for (int k = 0; k < 4; ++k) {
					curr_line->next = new ColoredNode(colors[(j+1)%4], false);  //create colored line for home
					curr_line = curr_line->next;
					places[p--]=curr_line->piececount;
				}
				curr_line->next = win;

				for (int i = 0; i < 7; ++i) {
					current->next = new Node(true);		//7 normal nodes
					current = current->next;
				}

				current->next = new Node(false);		//1 non kill code
				current = current->next;

				for (int i = 0; i < 2; ++i) {
					current->next = new Node(true);		//2 normal nodes
					current = current->next;
				}

				current->next = new ExtendedColoredNode(colors[(j+1)%4], lines[(j+1)%4], true);		//1 special node
				current = current->next;

				current->next = new Node(true);			//1 normal nodes
				current = current->next;


				colorjails[(j+1)%4]->next = colorstart[(j+1)%4] = current->next = new Node(false);	//1 next node's start point
				current=current->next;
			}
			// Make it circular
			head=win->next;
			current->next = head;
			win->next = NULL;	//detach win from board.

			int q=0;
			current=head;
			while(current->next != head) {
				places[q]=current->piececount;
				*(places[q])=0;
				current=current->next;
				q++;
			}

			//other values specific for display function only
			for(int z=0; z<72; z++) {
				*places[z]=0;
			}
		}

		void UpdatePlaceArr() {	//updates all places on board for display
			int q=0;
			Node* current=head;
			while(current->next != head) {
				*(places[q])=*(current->piececount);
				current=current->next;
				q++;
			}
			*(places[q])=*(current->piececount);
			current=current->next;
			int z=71;
			Node* l = lines[1];
			while(l->next!=NULL) {	//updates places on board
				int bm = *(places[z]);
				*(places[z])=*(l->piececount);
				l=l->next;
				z--;
			}
		}

		void updatejail(int t, int p) {  //updates jails on...
			if(p==2) {
				(*(colorjails[t]->piececount))--;	//free piece
			} else if(p==3) {
				(*(colorjails[t]->piececount))++;	//piece capture
			}
		}

		void display() {
			cout<<"////////////////////////////////////////////////////////////////////////\n";
			cout<<"//                            [NEW TURN]                              //\n";
			cout<<"////////////////////////////////////////////////////////////////////////\n";
			UpdatePlaceArr();
			SetConsoleTextAttribute(hConsole,  RED);
			printf("%2d          ",*(colorjails[0]->piececount));
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d%2d%2d",*(places[9]),*(places[10]),*(places[11]));
			SetConsoleTextAttribute(hConsole,  GREEN);
			printf("          %2d",*(colorjails[1]->piececount));
			SetConsoleTextAttribute(hConsole,  0);
			cout<<endl;

			SetConsoleTextAttribute(hConsole,  RED);
			printf("            ");
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d",*(places[8]));
			SetConsoleTextAttribute(hConsole,  GREEN);
			printf("%2d%2d            ",*(places[71]),*(places[12]));
			SetConsoleTextAttribute(hConsole,  0);
			cout<<endl;
			
			for(int  i=0;  i<4;  i++)  {
				SetConsoleTextAttribute(hConsole,  RED);
				printf("            ");
				SetConsoleTextAttribute(hConsole,  WHITE);
				printf("%2d",*(places[7-i]));
				SetConsoleTextAttribute(hConsole,  GREEN);
				printf("%2d",*(places[70-i]));
				SetConsoleTextAttribute(hConsole,  WHITE);
				printf("%2d",*(places[13+i]));
				SetConsoleTextAttribute(hConsole,  GREEN);
				printf("            ");
				SetConsoleTextAttribute(hConsole,  0);
				cout<<endl;
			}

			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d",*(places[50]));
			SetConsoleTextAttribute(hConsole,  RED);
			printf("%2d",*(places[51]));
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d%2d%2d%2d",*(places[0]),*(places[1]),*(places[2]),*(places[3]));
			SetConsoleTextAttribute(hConsole,  CYAN);
			printf("      ");
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d%2d%2d%2d%2d%2d",*(places[17]),*(places[18]),*(places[19]),*(places[20]),*(places[21]),*(places[22]));
			SetConsoleTextAttribute(hConsole,  0);
			cout<<endl;
			
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d",*(places[49]));
			SetConsoleTextAttribute(hConsole,  RED);
			printf("%2d%2d%2d%2d%2d",*(places[56]),*(places[55]),*(places[54]),*(places[53]),*(places[52]));
			SetConsoleTextAttribute(hConsole,  CYAN);
			printf("  %2d  ",*(win->piececount));
			SetConsoleTextAttribute(hConsole,  PURPLE);
			printf("%2d%2d%2d%2d%2d",*(places[62]),*(places[63]),*(places[64]),*(places[65]),*(places[66]));
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d",*(places[23]));
			SetConsoleTextAttribute(hConsole,  0);
			cout<<endl;

			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d%2d%2d%2d%2d%2d",*(places[48]),*(places[47]),*(places[46]),*(places[45]),*(places[44]),*(places[43]));
			SetConsoleTextAttribute(hConsole,  CYAN);
			printf("      ");
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d%2d%2d%2d",*(places[29]),*(places[28]),*(places[27]),*(places[26]));
			SetConsoleTextAttribute(hConsole,  PURPLE);
			printf("%2d",*(places[25]));
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d",*(places[24]));
			SetConsoleTextAttribute(hConsole,  0);
			cout<<endl;

			for(int  i=0;  i<4;  i++)  {
				SetConsoleTextAttribute(hConsole,  BLUE);
				printf("            ");
				SetConsoleTextAttribute(hConsole,  WHITE);
				printf("%2d",*(places[42-i]));
				SetConsoleTextAttribute(hConsole,  BLUE);
				printf("%2d",*(places[57+i]));
				SetConsoleTextAttribute(hConsole,  WHITE);
				printf("%2d",*(places[30+i]));
				SetConsoleTextAttribute(hConsole,  PURPLE);
				printf("            ");
				SetConsoleTextAttribute(hConsole,  0);
				cout<<endl;
			}

			SetConsoleTextAttribute(hConsole,  BLUE);
			printf("            %2d%2d",*(places[38]),*(places[61]));
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d",*(places[34]));
			SetConsoleTextAttribute(hConsole,  PURPLE);
			printf("            ");
			SetConsoleTextAttribute(hConsole,  0);
			cout<<endl;

			SetConsoleTextAttribute(hConsole,  BLUE);
			printf("%2d          ",*(colorjails[3]->piececount));
			SetConsoleTextAttribute(hConsole,  WHITE);
			printf("%2d%2d%2d",*(places[37]),*(places[36]),*(places[35]));
			SetConsoleTextAttribute(hConsole,  PURPLE);
			printf("          %2d",*(colorjails[2]->piececount));
			SetConsoleTextAttribute(hConsole,  15);
			cout<<endl;
			
			SetConsoleTextAttribute(hConsole, 15);
			return;
		}
};

#endif