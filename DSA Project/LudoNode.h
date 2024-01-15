#include<iostream>
using namespace std;

#ifndef LUDONODE_H
#define LUDONODE_H

class Node {
	public:
		int* piececount;
		bool kill;
		Node* next;
		Node(bool nodeKill = false) : next(NULL), kill(nodeKill), piececount(new int) {}
		virtual ~Node() {}
};

class ColoredNode : public Node {
	public:
		string color;
		ColoredNode(const string& nodeColor, bool nodeKill = false) : Node(nodeKill), color(nodeColor) {}
};

class ExtendedColoredNode : public ColoredNode {
	public:
		Node* home;
		ExtendedColoredNode(const string& nodeColor, Node* nodeHome, bool nodeKill = false) : ColoredNode(nodeColor, nodeKill), home(nodeHome) {}
};

#endif