#include "Symbol_table.h"
#include "Token.h"

vector<Variable> var_table;

double Symbol_table::get(string s)
{
	for (Variable& v : var_table)
		if (v.name == s)
			return v.value;

	runtime_error("get: undefined name " + s);
}

void Symbol_table::set(string s, double d)
{
	for (Variable& v : var_table)
	{
		if (v.name == s)
		{
			v.value = d;
			return;
		}
	}

	runtime_error("set: undefined name "+ s);
}

int Symbol_table::is_declared(string s)
{
	for (Variable& v : var_table)
		if (v.name == s)
		{
			if (v.kind == con) return 1;
			return 2;
		}
	return 3;
}

double Symbol_table::define(string var, double val, char type)
{
	if (is_declared(var) == 2) 
	{
		set(var, val);
		return val;
	}

	var_table.push_back(Variable{ var, val, type});

	return val;
}