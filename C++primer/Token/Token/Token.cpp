#include "Token.h"
#include <string>

Token & Token::operator=(int i)
{
	// TODO: 在此处插入 return 语句
	if (tok == STRING)sval.std::string::~basic_string();
	tval = i;
	tok = INT;
	return *this;
}

Token & Token::operator=(const std::string &s)
{
	// TODO: 在此处插入 return 语句
	if (tok == STRING)
		sval = s;
	else
		new(&sval) std::string(s);
	tok = STRING;
	return *this;
}


void Token::copyToke(const Token &t)
{
	switch (t.tok)
	{
	case Token::INT:tval = t.tval;break;
	case Token::CHAR:cval = t.cval;break;
	case Token::DOUBLE:dval = t.dval; break;
	case Token::STRING:new(&sval) std::string(t.sval); break;
	default:
		break;
	}
}

std::ostream & operator<<(std::ostream & os, const Token & t)
{
	// TODO: 在此处插入 return 语句
	switch (t.tok)
	{
	case Token::INT:os << t.tval; break;
	case Token::CHAR:os << t.cval; break;
	case Token::DOUBLE:os << t.dval; break;
	case Token::STRING:os << t.sval; break;
	default:
		break;
	}
	return os;
}
