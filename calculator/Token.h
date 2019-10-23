#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

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
	Token_stream() : in{ cin } { }
	Token_stream(istream& s) : in{ s } { }

	Token get();
	void putback(Token t);

	void ignore(char);


private:
	//...
	istream& in;
};

constexpr char q = 'q';
constexpr char h = 'h';
constexpr char print1 = ';';
constexpr char print2 = '\n';
constexpr char print3 = '\0';
constexpr char spase = ' ';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char con = 'ñ';
constexpr char non = 'n';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string constant = "const";
const string quit = "quit";
const string help = "help";
