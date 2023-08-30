#pragma once

#include <stack>
#include <exception>

class RPN {
private:
	std::stack<int>		stack;

public:
	RPN();
	RPN(const RPN &);
	virtual ~RPN();
	RPN&	operator=(const RPN &);

	void insert(int i);
	void add();
	void sub();
	void div();
	void mul();
	int eval();
};
