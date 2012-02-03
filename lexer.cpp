#include "lexer.h"
#include <cctype>
#include <iostream>
#include <cstdio>
using namespace std;

void lexer::getToken() {
	discard_whitespace();

	int tok = cin.peek();
	switch (tok) {
		case '\n':
			_token = tok;
			// we don't cin.get() because we're about to flush_line().
			return;
		case '@':
		case '%':
		case '&':
		case '(':
		case ')':
			_token = tok;
			cin.get();
			return;
		case EOF:
			_token = "";
			return;
		default:
			if (isdigit(tok)) {
				_token = "";
				do {
					_token += cin.get();
				} while (isdigit(cin.peek()));
				return;
			}
	}
	// We have found an unknown token! Oh dear me!
	cout << "line " << line_no() << " lexical error\n";
	//std::cout << "line " << line_no() << " lexical error: "
	//	"unknown char " << (char) tok << " (" << tok << ")\n";
	is_error = true;
}
