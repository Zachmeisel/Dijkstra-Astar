#pragma once
#include <iostream>
#include <list>
#include <vector>
class Nodes
{
public:
	Nodes();
	~Nodes();

	bool open;
	bool end;
	bool path;
	int num1, num2;
	std::vector<std::pair<Nodes*,int> > adjacent;
	
	

};

