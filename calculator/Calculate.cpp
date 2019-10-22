#include "Calculate.h"

void calculate()
{
	Symbol_table st;

	while (true)
	{
		cout << prompt;
		string s;
		getline(cin, s);
		vector<string> str = { split(s) };
		bool d1 = detect1(s);
		for (int i = 0; i < str.size(); ++i)
		{
			istringstream is{ str[i] };
			Token_stream ts(is);
			try
			{
				Token t = ts.get();
				while (t.kind == print1 or t.kind == print2 or t.kind == print3)
					if(!is.eof())
						t = ts.get();
				if (t.kind == q) return;
				if (t.kind == h)
				{
					print_help();
					continue;
				}
				ts.putback(t);
				cout << result << statement(ts, st, d1) << endl;
				t = ts.get();
				if (t.kind != print1)
					throw runtime_error("Wrong input");
			}
			catch (exception & e)
			{
				cerr << e.what() << endl;
				ts.ignore(print1);
			}
		}
	}
}