#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <iostream>

int main(int ac, char **av) {
	PmergeMe fja;

	if (ac <= 1)
	{
		std::cout << "provide at least 1 argument\n";
		return 0;
	}
	for (int i = 1; i < ac; ++i)
	{
		char * c;
	   unsigned long int nb = strtoul(av[i], &c, 10);
	   if (!c || *c || nb > INT_MAX) {
		   std::cout << "argument " << i << " is not a positive integer : " << av[i] << std::endl;
		   return 0;
	   }
	   fja.insert(nb);
	}
	fja.sort();
}
