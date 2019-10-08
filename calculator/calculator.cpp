//
//       Calculator
//

#include "Token.h"
#include "Variable.h"

double expression(Token_stream& ts);

double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '{':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != '}') error("'}' exepcted");
		return d;
	}
	case '-':
		return -primary(ts);
	case '+':
		return +primary(ts);
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term(Token_stream& ts)
{
	double left = primary(ts);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '*':
		{
			left *= primary(ts);
			break;
		}
		case '/':
		{
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left = fmod(left, d);
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression(Token_stream& ts)
{
	double left = term(ts);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '+':
			left += term(ts);
			break;

		case '-':
			left -= term(ts);
			break;

		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration(Token_stream& ts)
{
	Token t = ts.get();
	char c = non;
	if (t.kind == con)
	{
		c = con;
		t = ts.get();
	}

	if (t.kind != name)
		error("name expected in declaration");

	string var = t.name;
	if (is_declared(var) == 1)
		error(var, " declared twice");

	t = ts.get();
	if (t.kind != '=')
		error("'=' missing in declaration of ", var);

	double d = expression(ts);
	define_name(var, d, c);
	return d;
}

double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration(ts);
	default:
		ts.putback(t);
		return expression(ts);
	}
}

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

void calculate()
{
	Token_stream ts;

	while (true)
		try{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
			t = ts.get();
		if (t.kind == quit) return;

		ts.putback(t);
		cout << result << statement(ts) << endl;
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
	define_name("pi", 3.141592653589793, con);
	define_name("e", 2.718281828459045, con);

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
