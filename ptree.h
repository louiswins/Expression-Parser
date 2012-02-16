#ifndef PTREE_H
#define PTREE_H

#include <iostream>
#include <tr1/memory>

class ptree {
public:
	typedef std::tr1::shared_ptr<ptree> ptr;
	virtual int eval() const = 0;
	void print() const { print(0); }
	virtual void print(int indent) const = 0;
	virtual ~ptree() {}
};

class int_literal : public ptree {
public:
	int_literal(int value) : v(value) {}
	int eval() const { return v; }
	void print(int indent) const {
		while (indent--) std::cout << "   ";
		std::cout << v << "\n";
	}

private:
	int v;
};

class amp_operator : public ptree {
public:
	amp_operator(ptree::ptr left, ptree::ptr right) : l(left), r(right) {}
	amp_operator(ptree *left, ptree *right) : l(left), r(right) {}
	int eval() const;
	void print(int indent) const;
private:
	ptree::ptr l;
	ptree::ptr r;
};
class at_operator : public ptree {
public:
	at_operator(ptree::ptr left, ptree::ptr right) : l(left), r(right) {}
	at_operator(ptree *left, ptree *right) : l(left), r(right) {}
	int eval() const;
	void print(int indent) const;
private:
	ptree::ptr l;
	ptree::ptr r;
};
class pct_operator : public ptree {
public:
	pct_operator(ptree::ptr tree) : t(tree) {}
	pct_operator(ptree *tree) : t(tree) {}
	int eval() const;
	void print(int indent) const;
private:
	ptree::ptr t;
};

#endif /* PTREE_H */
