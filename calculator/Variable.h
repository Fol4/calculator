#pragma once
#include"Token.h"

struct Variable
{
	string name;
	double value;
	char kind;

	Variable(string n, double v, char c): name{ n }, value{ v }, kind{ c } { }
};


