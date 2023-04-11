#pragma once
#include "Node.h"
#include "fstream"
class PrintManager
{
private:
	int timeIndex = 0;
	int TimeCount = 0;
	int count = 0;
	int cnt = 0;
	int index = 0;
	int arr[5] = { 0,1,2,3,4 };
	int x = 1;
	int y = 1;
	string TimeCountStr;
	string filename;
	ifstream file;
	Node T[5];
	Node FinishedNodes;
	Node* end = nullptr;
	Node* p;
	bool finished = false;
public:
	PrintManager(string t);//We can load the file in the constructor
	void LoadFile();
	void addNode(int i, string d, int t);
	void deleteNode(int i, string d);
	void PrintNode(Node T[]);
	void UpdateNodes(int i);
	void MakeBoxes();
	void MakeNodeBox(int i);
	void ShowConsoleCursor(bool showFlag);
	void getTime();

};