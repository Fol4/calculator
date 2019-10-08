#include "Variable.h"
#include "Token.h"

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

int is_declared(string s)
{
	for (Variable& v : var_table)
		if (v.name == s)
		{
			if (v.kind == con) return 1;
			return 2;
		}
	return 3;
}

double define_name(string var, double val, char type)
{
	if (is_declared(var) == 2) 
	{
		set_value(var, val);
		return val;
	}

	var_table.push_back(Variable{ var, val, type});

	return val;
}