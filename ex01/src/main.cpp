#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av) {
	RPN rpn;
	if (ac != 2) {
		std::cerr << "Error: usage ./RPN expr\nexpr : expretion in reverse polish notation\n\tevery digit are interpreted separatly\n\tevery caracter other than 0123456789+-/* are ignored\n";
		return 0;
	}
	char *expr = av[1];
	try {
	while (*expr) {
		if (*expr >= '0' && *expr <= '9')
			rpn.insert(*expr - '0');
		else switch (*expr) {
			case '+':
				rpn.add();
				break;
			case '-':
				rpn.sub();
				break;
			case '/':
				rpn.div();
				break;
			case '*':
				rpn.mul();
				break;
			default: ;
		}
		++expr;
	}
	std::cout << rpn.eval() << std::endl;
	}
	catch (std::exception &e) {
		(void) e;
		std::cerr << "Error\n";
	}
}
