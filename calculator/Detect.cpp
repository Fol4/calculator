#include "Detect.h"
bool detect1(string s)
{
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == '=')
			return true;
	return false;
}

bool detect2(string s)
{
	for (int i = 0; i < s.length(); ++i)
		if (s[i] != spase)
			return true;
	return false;
}

string delete_spase(string s)
{
	string s1;
	for (int i = 0; i < s.length(); ++i)
		if (s[i] != ' ' and s[i] != '\t')
			s1 += s[i];
	return s1;
}

bool detect3(string s)
{
	string s1 = delete_spase(s);
		for (int i = 0; i < s1.length() - 2; ++i)
			if ((s1[i] == '-' or s1[i] == '+') and s1[i + 1] == '-' )
				return true;

	return false;
}

bool detect4(string s)
{

	if (s[0] == '.')
	{
		if (s.length() == 1)
			return true;
		else if (!isdigit(s[1]))
			return true;
	}
	for (int i = 1; i < s.length(); ++i)
		if (s[i] == '.' and (s[i - 1] == '.' or s[i - 1] == ' '))
			return true;

	return false;
}

int factorial(int i)
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}