#include "Calculate.h"

void calculate()
{
	Token_stream ts;
	Symbol_table st;

	while (true)
		try {
		cout << prompt;
		string s;
		getline(cin, s);
		vector<string> str = { split(s) };
		for (int i = 0; i < str.size(); ++i)
		{
			istringstream is{ str[i] };
			Token_stream ts(is);
			Token t = ts.get();
			while (t.kind == print1 || t.kind == print2 || t.kind == print3)
				t = ts.get();
			if (t.kind == q) return;
			if (t.kind == h)
			{
				print_help();
				continue;
			}
			ts.putback(t);
			cout << result << statement(ts, st) << endl;
		}
	}
	catch (exception & e)
	{
		cerr << e.what() << endl;
		clean_up_mess(ts);
	}
}