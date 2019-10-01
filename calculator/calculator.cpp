//
//       Calculator
//

#include <std_lib_facilities.h>

struct Token
{
	char kind;
	double value;
	string name;

	Token(char ch) : kind{ ch } { }
	Token(char ch, double val) : kind{ ch }, value{ val } { }
	Token(char ch, string n) : kind{ ch }, name{ n } { }
};

class Token_stream
{
	bool full{ false };
	Token buffer{ '0' };

public:
	Token_stream() { }

	Token get();
	void putback(Token t);

	void ignore(char);
};

void Token_stream::putback(Token t)
{
	if (full)
		error("putback() into a full buffer");

	buffer = t;
	full = true;
}

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch)
	{
	case 'q':
	case '(':
	case ')':
	case '{':
	case '}':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
		return Token{ ch };

	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ number, val };
	}

	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) &&
				(isalpha(ch) || isdigit(ch)))
				s += ch;
			cin.putback(ch);

			if (s == declkey) return Token(let);

			return Token{ name, s };
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable
{
	string name;
	double value;

	Variable(string n, double v)
		: name{ n }, value{ v }
	{ }
};

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
	if (t.kind != name)
		error("name expected in declaration");

	string var = t.name;
	if (is_declared(var))
		error(var, " declared twice");

	t = ts.get();
	if (t.kind != '=')
		error("'=' missing in declaration of ", var);
	double d = expression(ts);
	define_name(var, d);
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
	while (cin)
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
	define_name("pi", 3.141592653589793);
	define_name("e", 2.718281828459045);

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
