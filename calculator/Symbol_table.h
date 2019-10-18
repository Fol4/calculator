#pragma once
#include "Variable.h"

using namespace std;

class Symbol_table
{
private:

	vector<Variable> var_table;

public:

	double get(string s);
	void set(string s, double d);
	int is_declared(string s);
	double define(string var, double val, char type);
};