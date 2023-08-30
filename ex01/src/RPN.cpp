#include "RPN.hpp"

RPN::RPN():stack() {;}
RPN::RPN(const RPN &src):stack(src.stack) {;}
RPN::~RPN() {;}

RPN&	RPN::operator=(const RPN &src) {
	if (this == &src) return (*this);
	this->stack = src.stack;
	return (*this);
}

void RPN::insert(int i) {
	this->stack.push(i);
}

void RPN::add() {
	if (this->stack.size() < 2)
		throw std::exception();
	int i,j;
	i = this->stack.top();
	this->stack.pop();
	j = this->stack.top();
	this->stack.pop();
	this->stack.push(j+i);
}

void RPN::sub() {
	if (this->stack.size() < 2)
		throw std::exception();
	int i,j;
	i = this->stack.top();
	this->stack.pop();
	j = this->stack.top();
	this->stack.pop();
	this->stack.push(j-i);
}

void RPN::div() {
	if (this->stack.size() < 2)
		throw std::exception();
	int i,j;
	i = this->stack.top();
	if (!i) throw std::exception();
	this->stack.pop();
	j = this->stack.top();
	this->stack.pop();
	this->stack.push(j/i);
}

void RPN::mul() {
	if (this->stack.size() < 2)
		throw std::exception();
	int i,j;
	i = this->stack.top();
	this->stack.pop();
	j = this->stack.top();
	this->stack.pop();
	this->stack.push(j*i);
}

int RPN::eval() {
	if (this->stack.size() != 1)
		throw std::exception();
	return this->stack.top();
}
