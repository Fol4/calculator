#pragma once
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

struct Variable
{
	string name;
	double value;
	char kind;

	Variable(string n, double v, char c): name{ n }, value{ v }, kind{ c } { }
};


