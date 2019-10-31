#include "Symbol_table.h"

vector<Variable> var_table;

double Symbol_table::get(string s)
{
	for (Variable& v : var_table)
		if (v.name == s)
			return v.value;

	throw runtime_error("get: undefined name " + s);
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

	throw runtime_error("set: undefined name "+ s);
}
declared Symbol_table::is_declared(string s)
{
	for (Variable& v : var_table)
		if (v.name == s)
		{
			if (v.kind == con) return declared::is_constant;
			return declared::is_nonconstant;
		}
	return declared::is_not_declared;
}

double Symbol_table::define(string var, double val, char type)
{
	if (is_declared(var) == declared::is_nonconstant)
	{
		set(var, val);
		return val;
	}

	var_table.push_back(Variable{ var, val, type});

	return val;
}

unsigned int Symbol_table:: var_number() const
{
	return var_table.size();
}
const Variable& Symbol_table::get_val(unsigned int i) const
{
	if (i <= var_number())
		return var_table[i];
	throw runtime_error("Not found");
}