Expression Parser
=================

This is a simple implementation of a top-down recursive descent parser written
in C++. It is separated into two classes, a lexer and a parser, each of which
has a relatively clean interface.

The mathematical expressions that this program parses are of a peculiar form.
It doesn't use the familiar +, -, \*, / operators; instead, we have defined
three of our own.

* The ampersand `&`: `a & b` is defined to be `gcd(a+2, b+3)`,
* The percent sign `%`: `% a` is defined to be `max(5\*a, (3\*a+10))`, and
* The at symbol `@`: `a @ b` is defined to be `(a+5) mod b`.

They are in order of precedence `&` < `%` < `@`, i.e., `%3@4&5` means
`(%(3@4))&5`.  Additionally, `@` is right-associative while & is
left-associative.

Parentheses can be used for grouping.
