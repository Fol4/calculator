#include "Variable.h"

vector<Variable> var_table;

double get_value(string s)
{
	for (Variable& v : var_table)
		if (v.name == s)
			return v.value;

	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (Variable& v : var_table)
	{
		if (v.name == s)
		{
			v.value = d;
			return;
		}
	}

	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (Variable& v : var_table)
		if (v.name == s) return true;
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var))
		error(var, " declared twice");

	var_table.push_back(Variable{ var, val });

	return val;
}