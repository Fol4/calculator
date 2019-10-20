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
		if (t.kind != ')') runtime_error("'(' expected");
		return d;
	}
	case '{':
	{
		double d = expression(ts, st);
		t = ts.get();
		if (t.kind != '}') runtime_error("'}' exepcted");
		return d;
	}
	case '-':
		return -primary(ts, st);
	case '+':
		return +primary(ts, st);
	case number:
		return t.value;
	case name:
		return st.get(t.name);
	default:
		runtime_error("primary expected");
	}
}

double term(Token_stream& ts, Symbol_table& st)
{
	double left = primary(ts, st);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '*':
		{
			left *= primary(ts, st);
			break;
		}
		case '/':
		{
			double d = primary(ts, st);
			if (d == 0) runtime_error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = primary(ts, st);
			if (d == 0) runtime_error("divide by zero");
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
	if (st.is_declared(var) == 1) throw runtime_error(var + " declared twice");
	else if (st.is_declared(var) == 2 && c == con) throw runtime_error(var + " not constant declared constant");

	t = ts.get();
	if (t.kind != '=') throw runtime_error("'=' missing in declaration of " + var);

	double d = expression(ts, st);
	st.define(var, d, c);
	return d;
}

double statement(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration(ts, st);
	default:
		ts.putback(t);
		return expression(ts, st);
	}
}

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print1);
	ts.ignore(print2);
	ts.ignore(print3);
}

vector<string> split(string s)
{
	string s1;
	vector<string> str;
	for (int i = 0; i < s.length(); ++i)
		if (i == s.length() - 1 && s[i] != ';')
		{
			s1 += s[i];
			s1 += ';';
			str.push_back(s1);
		}
		else if (s[i] == ';')
		{
			s1 += ';';
			str.push_back(s1);
			s1 = "";
		}
		else
			s1 += s[i];

	return str;
}

void print_help()
{
	cout << "123" << endl;
}
