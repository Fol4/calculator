#include "Token.h"

void Token_stream::putback(Token t)
{
	if (full)
		runtime_error("putback() into a full buffer");

	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	in.get(ch);
	while(ch == spase)
		in.get(ch);

	switch (ch)
	{
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
	case '\n':
		return Token{ ch };

	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		in.putback(ch);
		double val;
		in >> val;
		return Token{ number, val };
	}

	default:
		if (isalpha(ch) || (ch == '_'))
		{
			string s;
			s += ch;
			while (in.get(ch) &&
				(isalpha(ch) || isdigit(ch) || (ch == '_')))
				s += ch;
			in.putback(ch);

			if (s == declkey) return Token(let);
			if (s == constant) return Token(con);
			if (s == quit) return Token(q);
			if (s == help) return Token(h);

			return Token{ name, s };
		}
		runtime_error("Bad token");
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
	while (in >> ch)
		if (ch == print1 || ch == print2 || ch == print3) return;
}