#ifndef PARSER_H
#define PARSER_H

#include "ops.h"
#include <iostream>
#include <sstream>
#include <vector>

/* Sample lexer class just to test the parser */
class lexer {
public:
	void getToken() {
		if (!is_first) ++iter;
		is_first = false;
	}
	bool hasTokens() const {
		return iter != tokens.end();
	}

	lexer() {
		tokens.push_back("%");
		tokens.push_back("%");
		tokens.push_back("3");
		tokens.push_back("@");
		tokens.push_back("4");
		tokens.push_back("&");
		tokens.push_back("5");
		tokens.push_back("@");
		tokens.push_back("(");
		tokens.push_back("%");
		tokens.push_back("(");
		tokens.push_back("6");
		tokens.push_back("&");
		tokens.push_back("7");
		tokens.push_back(")");
		tokens.push_back(")");
		iter = tokens.begin();
		is_first = true;
	}
	std::string token() const {
		if (hasTokens())
			return *iter;
		else
			return "";
	}
	int line_no() const {
		return 1;
	}

private:
	bool is_first;
	std::vector<std::string> tokens;
	std::vector<std::string>::const_iterator iter;
};

class parser {
public:
	parser() {}
	parser(lexer _l) : l(_l) {}

	ptree_ptr read_expression();
private:
	ptree_ptr ampersand_op();
	ptree_ptr percent_op();
	ptree_ptr at_op();
	ptree_ptr term();
	ptree_ptr number();
	bool match(const std::string tok, const std::string msg);

	lexer l;
};

#endif /* PARSER_H */
