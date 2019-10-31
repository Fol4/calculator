#pragma once
#include "Detect.h"

//* Калькулятор
//* Работает с числами, переменными и константами
//* Состоит из 5 файлов(calculator.cpp, calculate.cpp, detect.h, detect.cpp, token.h, token.cpp, varible.h, varible.cpp)
//* Считывание происходит с помощью функции Token_stream::get
//* Граматика:
//*
//*calculatotion :
//*		exit,
//*		print,
//*		help,
//*		statement
//*
//*	exit:
//*		"quit"
//* print :
//*		";",
//*		"\n"
//*
//*statement :
//*		expression,
//*		a constant declaration,
//*		not a constant declaration,
//
//*assignment :
//*		expression,
//*		a constant assignment,
//*		not a constant assignment,
//*		
//*
//* a constant declaration :
//*		"let const" name "=" expression
//*	not a constant declaration :
//*		"let" name "=" expression
//* assignment :
//*		name "=" expression
//*
//*name : [a - z,A - Z] [a - z,A - Z,0 - 9,_] *
//*
//*expression :
//*		term "+" term,
//*		term "-" term,
//*		term;
//*term:
//*		secondary "*" secondary,
//*		secondary "/" secondary,
//*		secondary "%" secondary,
//		secondary
//* secondary:
//*		pow "(" expression "," expression ")",
//*		primary
//*
//* primary :
//*		"(" expression ")",
//*		"-" primary,
//*		number,
//*		constant,
//*		variable
//* detect:
//*		detec1,
//*		detect2,
//*		detect3,
//*		detect4,
//*		spase_delete,
//*		factorial
//* number: Вещественный литерал
//* constant : name
//	* varible : name


double primary(Token_stream& ts, Symbol_table& st);
double term(Token_stream& ts, Symbol_table& st);
double expression(Token_stream& ts, Symbol_table& st);
double declaration(Token_stream& ts, Symbol_table& st);
double statement(Token_stream& ts, Symbol_table& st, bool d);
void print_help(const Symbol_table& st);
vector<string> split(string s);
double assignment(Token_stream& ts, Symbol_table& st, bool d);
string read(const string& filename);


