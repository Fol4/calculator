//
//       Calculator
//

#include "Token.h"
#include "Symbol_table.h"

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
		return expression(ts,st);
	}
}

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

void calculate()
{
	Token_stream ts;
	Symbol_table st;

	while (true)
		try{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
			t = ts.get();
		if (t.kind == quit) return;

		ts.putback(t);
		cout << result << statement(ts, st) << endl;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		clean_up_mess(ts);
	}
}

int main()
try
{
	Symbol_table st;

	st.define("pi", 3.141592653589793, con);
	st.define("e", 2.718281828459045, con);

	calculate();
}
catch (exception& e)
{
	cerr << "exception: " << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Oops, unknown exception" << endl;
	return 2;
}
