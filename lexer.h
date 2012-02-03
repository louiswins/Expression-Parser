#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <cstdio>

class lexer {
public:
	lexer() : _line_no(1), is_error(false) {}

	void getToken();

	bool hasToken() const {
		// cin.eof() doesn't return true until you've tried to read a
		// character and failed.
		return std::cin.peek() != EOF;
	}
	
	bool good() const { return !is_error && std::cin.good(); }
	
	std::string token() const { return (is_error) ? "" : _token; }

	unsigned line_no() const { return _line_no; }

	void flush_line() {
		while (!std::cin.eof() && std::cin.get() != '\n');
		++_line_no;
		is_error = false;
	}

private:
	void discard_whitespace() {
		int c;
		while ((c = std::cin.peek()) == ' ' || c == '\t') {
			std::cin.get();
		}
	}

	unsigned _line_no;
	std::string _token;
	bool is_error;
};

#endif /* LEXER_H */
