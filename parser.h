#ifndef PARSER_H
#define PARSER_H

#include "ptree.h"
#include "lexer.h"
#include <string>

class parser {
public:
	parser() {}
	parser(lexer l) : _l(l) {}

	ptree_ptr read_expression();
	bool has_expression() const { return _l.hasToken(); }
private:
	ptree_ptr ampersand_op();
	ptree_ptr percent_op();
	ptree_ptr at_op();
	ptree_ptr term();
	ptree_ptr number();
	bool match(const std::string tok);

	lexer _l;
};

#endif /* PARSER_H */
