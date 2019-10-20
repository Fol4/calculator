#pragma once
#include "Symbol_table.h"

double primary(Token_stream& ts, Symbol_table& st);
double term(Token_stream& ts, Symbol_table& st);
double expression(Token_stream& ts, Symbol_table& st);
double declaration(Token_stream& ts, Symbol_table& st);
double statement(Token_stream& ts, Symbol_table& st);
void clean_up_mess(Token_stream& ts);
void print_help();
vector<string> split(string s);


