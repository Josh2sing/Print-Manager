#pragma once
#include <iostream>
using namespace std;

class Node
{
public:
	Node() { data = ""; time = -1; next = prev = nullptr; }
	Node(string d, int tm)
	{
		data = d;
		time = tm;
		next = prev = nullptr;
	}

	string data;
	int time;
	Node* next;
	Node* prev;
};