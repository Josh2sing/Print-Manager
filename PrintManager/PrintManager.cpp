#include <iostream>
#include "PrintManager.h"
#include "fstream"
#include <string>
#include "Node.h"
#include<windows.h>
#include<conio.h>
#include "Coordinates.h"
#include "MyRectangle.h"
#include <vector>
using namespace std;
PrintManager::PrintManager(string t)
{
	filename = t;
	LoadFile();
	UpdateNodes(0);
	//PrintNode(T);
	MakeBoxes();
	cout << endl << "Task Finished Successfully in: " << TimeCount << "Seconds";
}

void PrintManager::LoadFile()
{
	file.open(filename);
	string command, data;
	int location = 0;
	int Filetime = 0;
	Node T[5];
	string line;

	file >> command;
	if (command == "A")
	{
		file >> location >> data >> Filetime;
		addNode(location, data, Filetime);
	}
	else
	{
		file >> location >> data;
		deleteNode(location, data);
	}
	while (getline(file, line))
	{
		file >> command;
		if (command == "A")
		{
			file >> location >> data >> Filetime;
			addNode(location, data, Filetime);
		}
		else
		{
			file >> location >> data;
			deleteNode(location, data);
		}
	}
	//getTime();
	file.close();
}

void PrintManager::addNode(int location, string d, int Filetime)
{
	p = new Node(d, Filetime);
	if (T[location].next == nullptr)
	{
		T[location].next = p;
	}
	else
	{
		Node* t;
		t = &T[location];
		while (t->next != nullptr)
		{
			if (t->next->time > p->time)
			{
				p->next = t->next;
				t->next = p;
				break;
			}
			if (t->next->time < p->time)
			{
				t = t->next;
			}
		}
		t->next = p;
	}	
}

void PrintManager::deleteNode(int i, string d)
{
	p = new Node(d, 0);
	Node* t;
	t = &T[i];
	while (t->next != nullptr)
	{
		if (t->next->data == p->data)
		{
			p->next = t->next;
			t->next = t->next->next;
			delete(p->next);
			delete(p);
		}
		else
		{
			t = t->next;
		}
	}
}

void PrintManager::PrintNode(Node T[])
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Location " << i << ": ";
		Node* t;
		t = &T[i];
		while (t->next != nullptr)
		{
			cout << t->next->time << " ";
			t = t->next;
		}
		cout << endl;
	}
}

void PrintManager::UpdateNodes(int i)
{

	//While each node is not empty
	while (T != NULL)
	{
		ShowConsoleCursor(false);
		for (int rep = 0; rep < 5; rep++)
		{
			MakeBoxes();
			MakeNodeBox(rep);
			//cout << "TimeCount: " << TimeCount << endl;
			if (T[rep].next != nullptr)
			{
				//T[rep].next->time -= 1;
				if (T[rep].next->time < 1)
				{
					//T[rep].next->time--;
					deleteNode(rep, T[rep].next->data);
				}
			}
		}
		Sleep(1000);
		TimeCount++;
		system("cls");
		if (T == NULL)
			break;
		//PrintNode(T);
		//Create The main box on the left
		//Create Boxes on the right for each basically making another print function
		//Right Box for finished tasks
	}
			
}

void PrintManager::MakeBoxes()
{
	TimeCountStr = "Time Until Completion: " + to_string(TimeCount);
	MyRectangle CompletedTasks(80, 1, 20, 27, char(219), true, 2, 11, "");
	MyRectangle CompletedTasksLabel(80, 1, 20, 3, char(219), true, 2, 11, "Completed Tasks");
	//MyRectangle Timer(0, 0, 5, 1, NULL, true, 15, 15, TimeCountStr);
	MyRectangle Spacer(70, 1, 1, 27, '|' , true, 2, 11);
	CompletedTasksLabel.Draw();
	Spacer.Draw();
	//Timer.Draw();
	CompletedTasks.Draw();
	//Add a loop to create printer boxes
	for (int rep = 0; rep < 5; rep++)
	{
		string a = to_string(rep);
		MyRectangle curr(1, rep * 5 + 1, 9, 5, '.', true, rep + 1, 11, a);
		curr.Draw();

	}
}

void PrintManager::MakeNodeBox(int i)
{
	//Traverse the linked list and make a box for each
	int x = 0;
	int yNode = (arr[i] * 5) + 1;
	Node* t;
	t = &T[i];
	Node* start = T[i].next;
	if(t->next != nullptr)
		t->next->time--;
	while (t->next != nullptr)
	{
		if(t->next == nullptr)
			t->next->time--;
		string s = t->next->data + " " + to_string(t->next->time);
		x += 15;
		MyRectangle rect(x, yNode, 9, 5, '/' , true, 15, 15, s, 0);
		rect.Draw();
		if (t->next->time < 1)
		{
			rect.DrawPath("R47");
			rect.Impolode();
			p = new Node(T[i].next->data, T[i].next->time);
			if (FinishedNodes.next == nullptr)
			{
				FinishedNodes.next = p;
				end = p;
			}
			else
			{
				end->next = p;
				end = p;
			}
		}
		t = t->next;
	}
	int y = 5;
	Node* t2;
	t2 = FinishedNodes.next;
	while (t2 != nullptr)
	{
		MyRectangle rect2(82, y, 16, 5, (char) 219, true, 1, 15, t2->data);
		rect2.Draw();
		t2 = t2->next;
		y += 6;
	}
}

void PrintManager::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void PrintManager::getTime()
{
	for (int rep = 0; rep < 5; rep++)
	{
		Node* x;
		x = &T[rep];
		while (x->next != nullptr)
		{
			TimeCount += x->next->time;
			x = x->next;
		}
	}
}
