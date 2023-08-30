#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>

void swap(int &a, int &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void swap(void* &a, void* &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

class PmergeMe {
	std::vector<int> _tab;
	std::vector<int> _tab2;
	std::vector<int> *_cur;
	std::vector<int> *_swap;
public:
	sortVec() {
		int chunk = 1;
		std::vector<int>::iterator it, it2, itb, ite, its;
		itb = this->_cur->begin();
		ite = this->_cur->end();
		its = this=>_swap->begin();
		while (itb + 2 * chunk <= ite) { //recursivly make bigger pair
			it = itb + chunk - 1;
			while (it + chunk < ite) { //sort pair
				if (*(it) > *(it + chunk))
					for (int i = 0; i < chunk; ++i)
						swap(*(it - i), *(it + chunk - i));
				it += 2 * chunk;
			}
			chunk *= 2;
		}
		it = itb + chunk;
		while (it < ite) {
			*(its + it - itb) = *it;
			++it;
		}
		while (chunk > 1) {
			itb = this->_cur->begin();
			ite = this->_cur->end();
			its = this=>_swap->begin();

			chunk /= 2;
			it = itb + chunk;
			int i = (ite-itb)/chunk;
			it2 = its + i/2 + i%2;
			while (it + chunk < ite) { //put large element in swap vector 
				for (i = 0; i < chunk; ++i)
					*(it2 + i) = *(it + i);
				it += 2 * chunk;
				it2 += chunk;
			}
			//do small element
			it2 = its + i/2 + i%2;
			i = 1;
			while (it2 > its) {
				//i = 2*i + (i+1)%3 - 1;
				//find ???
				it2 -= chunk;
				for (int j = 0; j < chunk; ++j){
					for (int k = 0; k < ???; ++k)
						*(it2 + j + k*chunk) = *(is2 + j + k*chunk + chunk);
					*(it2 + j + k*chunk) = ???;
				}
			}
			swap(this->_cur, this->_swap);
		}
	}
};

int main() {
	int size = 1000;
	srand(time(0));
	int left = 0;
	int right = 0;

	pair tab[size];
	for (int i = 0; i < size; ++i)
		tab[i] = pair(rand(),rand());
	for (int i = 0; i < size; ++i) {
		int l = 0;
		for (int j = 0; j < i; ++j)
			l += tab[j].eval(tab[i].s);
		if (l*100/(size+i)>45)
			std::cout << l << " " << size + i - l << " " << ((double)l)/(double)(size+i)*100. << std::endl;
		left += l;
		right += size + i - l;
	}
	std::cout << left << " " << right << " " << ((double)left)/(double)(left + right)*100. << std::endl;
}
