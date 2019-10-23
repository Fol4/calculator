#include "Grammar.h"

double expression(Token_stream& ts, Symbol_table& st);

double primary(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression(ts, st);
		t = ts.get();
		if (t.kind != ')') throw  runtime_error("'(' expected");
		return d;
	}
	case '{':
	{
		double d = expression(ts, st);
		t = ts.get();
		if (t.kind != '}') throw runtime_error("'}' exepcted");
		return d;
	}
	case '-':
		return -primary(ts, st);
	case number:
	{
		auto temp = ts.get();
		if (temp.kind == '!') return factorial(t.value);
		ts.putback(temp);
		return t.value;
	}
	case name:
	{
		auto temp = ts.get();
		if (temp.kind == '!') return factorial(st.get(t.name));
		ts.putback(temp);
		return st.get(t.name);
	}
	default:
		throw runtime_error("primary expected");
	}
}

double sub_term(Token_stream& ts, Symbol_table& st)
{
	double left = primary(ts, st);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '^':
		{
			left = pow(left, primary(ts,st));
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}
double term(Token_stream& ts, Symbol_table& st)
{
	double left = sub_term(ts, st);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '*':
		{
			left *= sub_term(ts, st);
			break;
		}
		case '/':
		{
			double d = sub_term(ts, st);
			if (d == 0) throw runtime_error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = sub_term(ts, st);
			if (d == 0) throw runtime_error("divide by zero");
			left = fmod(left, d);
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression(Token_stream& ts, Symbol_table& st)
{
	double left = term(ts, st);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '+':
			left += term(ts, st);
			break;

		case '-':
			left -= term(ts, st);
			break;

		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();
	char c = non;
	if (t.kind == con)
	{
		c = con;
		t = ts.get();
	}

	if (t.kind != name) throw runtime_error("name expected in declaration");

	string var = t.name;
	if (st.is_declared(var) == 2) throw runtime_error(var + " declared twice");

	t = ts.get();
	if (t.kind != '=') throw runtime_error("'=' missing in declaration of " + var);

	double d = expression(ts, st);
	st.define(var, d, c);
	return d;
}

double assignment(Token_stream& ts, Symbol_table& st, bool d1)
{
	Token t = ts.get();
	char c = non;

	if (t.kind != name) throw runtime_error("name expected in declaration");

	string var = t.name;
	if (st.is_declared(var) == 1) throw runtime_error(var + " is constant");
	else if (st.is_declared(var) == 3) throw runtime_error(var + " not declared");

	double d;
	if (d1)
	{
		t = ts.get();
		d = expression(ts, st);
		st.define(var, d, c);
	}
	else
	{
		ts.putback(t);
		d = expression(ts, st);
	}

	return d;
}

double statement(Token_stream& ts, Symbol_table& st, bool d)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration(ts, st);
	case name:
		ts.putback(t);
		return assignment(ts, st, d);
	default:
		ts.putback(t);
		return expression(ts, st);
	}
}


vector<string> split(string s)
{
	string s1 = "";
	vector<string> str;
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == ';')
		{
			if (detect2(s1))
			{
				s1 += ';';
				str.push_back(s1);
				s1 = "";
			}
			else
				s1 = "";
		}
		else if (i == s.length() - 1)
		{
			s1 += s[i];
			if (detect2(s1))
			{
				s1 += ';';
				str.push_back(s1);
			}
		}
		else
			s1 += s[i];

	return str;
}

void print_help()
{
	cout << "123" << endl;
}
