//
//       Calculator
//

#include "Calculate.h"

int main()
try
{
	Symbol_table st;
	st.define("pi", 3.141592653589793, con);
	st.define("e", 2.718281828459045, con);

	calculate(st);
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
