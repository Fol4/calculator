#pragma once
#include "Detect.h"

double primary(Token_stream& ts, Symbol_table& st);
double term(Token_stream& ts, Symbol_table& st);
double expression(Token_stream& ts, Symbol_table& st);
double declaration(Token_stream& ts, Symbol_table& st);
double statement(Token_stream& ts, Symbol_table& st, bool d);
void print_help();
vector<string> split(string s);
double assignment(Token_stream& ts, Symbol_table& st, bool d);


