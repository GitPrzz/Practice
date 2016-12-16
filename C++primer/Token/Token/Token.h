#pragma once
#include <string>
#include <cstdio>
#include <iostream>

class Token
{
public:
	Token() :tval(0), tok(INT) {}
	Token(const Token& t) :tok(t.tok) { copyToke(t); }
	Token &operator=(const Token&);
	Token &operator=(int);
	Token &operator=(char);
	Token &operator=(double);
	Token &operator=(const std::string&);
	
	~Token() { if (tok == STRING) sval.std::string::~string();
		/*typedef basic_string<char> string;*/
	}
	friend std::ostream& operator<<(std::ostream& os, const Token&t);
private:
	enum { INT, CHAR, DOUBLE, STRING } tok;
	union { int tval; char cval; double dval; std::string sval; };
	void copyToke(const Token&);
};