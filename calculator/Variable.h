#pragma once
#include <std_lib_facilities.h>

struct Variable
{
	string name;
	double value;
	char kind;

	Variable(string n, double v, char c): name{ n }, value{ v }, kind{ c } { }
};

double get_value(string s);
void set_value(string s, double d);
int is_declared(string s);
double define_name(string var, double val, char type);

