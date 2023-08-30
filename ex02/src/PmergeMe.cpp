#include "PmergeMe.hpp"
#include <iostream>

static void swap(int &a, int &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

static std::ostream& operator<<(std::ostream& os, const std::vector<int> &vec) {
	for (std::vector<int>::const_iterator it = vec.begin(); it < vec.end(); ++it)
		os << ' ' << *it;
	return os;
}

PmergeMe::PmergeMe():_tab(),_tab2(),_cur(&(this->_tab)),_swap(&(this->_tab2)),_que(),_que2(),_qcur(&(this->_que)),_qswap(&(this->_que2)) {}
PmergeMe::PmergeMe(const PmergeMe &src):_tab(src._tab),_tab2(src._tab2),_cur(src._cur),_swap(src._swap),_que(src._que),_que2(src._que2),_qcur(src._qcur),_qswap(src._qswap) {}
PmergeMe::~PmergeMe() {}

PmergeMe&	PmergeMe::operator=(const PmergeMe &src) {
	if (this == &src) return (*this);
	this->_tab = src._tab;
	this->_tab2 = src._tab2;
	this->_cur = src._cur;
	this->_swap = src._swap;
	this->_que = src._que;
	this->_que2 = src._que2;
	this->_qcur = src._qcur;
	this->_qswap = src._qswap;
	return (*this);
}

void PmergeMe::insert(int i) {
	this->_tab.push_back(i);
	this->_tab2.push_back(i);
	this->_que.push_back(i);
	this->_que2.push_back(i);
}

void PmergeMe::sortVec() {
	int chunk = 1;
	std::vector<int>::iterator it, it2, itb, ite, its;
	itb = this->_cur->begin();
	ite = this->_cur->end();
	its = this->_swap->begin();
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
	while (it < ite) { //copy trailing element
		*(its + (it - itb)) = *it;
		++it;
	}


	while (chunk > 1) { //sorting loop
		itb = this->_cur->begin();
		ite = this->_cur->end();
		its = this->_swap->begin();
		chunk /= 2;
		it = itb + chunk;
		int i = (ite-itb)/chunk;
		it2 = its + (i/2 + i%2) * chunk;
		while (it + chunk <= ite) { //put large element in swap vector 
			for (int j = 0; j < chunk; ++j) 
				*(it2 + j) = *(it + j);
			it += 2 * chunk;
			it2 += chunk;
		}
		//do small element
		it2 = its + (i/2 + i%2) * chunk - 1; //were the search begin
		for (i = 0; i < chunk; ++i) { // first one is alway free
			*it2 = *(itb + chunk - 1 - i);
			--it2;
		}
		int jac = 0; //jacobsthal number - 1
		it = itb + 5*chunk - 1; //element to swap
		if (it >= ite) it -= 2 * chunk;
		int maxsearch = 2;
		while (it2 >= its) { //insert current chunk size
			if (it == itb + chunk - 1 + jac * 2 * chunk) { //advance the jacosthal
				jac = 2*jac + 2 - (jac&3);
				it = itb + chunk - 1 + (2*jac + 2 - (jac&3)) * 2 * chunk;
				while (it >= ite) it -= 2*chunk;
				maxsearch *= 2;
			}
			int insert = 0;
			for (int j = maxsearch; j > 0; j = j >> 1) { //search were to insert
				if (it2 + chunk * (insert + j) < this->_swap->end() && *it > *(it2 + chunk * (insert + j)))
					insert += j;
			}
			for (int j = 0; j < chunk; ++j){ //put the element at the right place
				for (int k = 0; k < insert; ++k)
					*(it2 + k*chunk) = *(it2 + k*chunk + chunk);
				*(it2 + insert*chunk) = *it;
				--it;
				--it2;
			}
			it -= chunk;
		}
		swap(this->_cur, this->_swap);
	}
}

void PmergeMe::sortQue() {
	int chunk = 1;
	std::deque<int>::iterator it, it2, itb, ite, its;
	itb = this->_qcur->begin();
	ite = this->_qcur->end();
	its = this->_qswap->begin();
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
	while (it < ite) { //copy trailing element
		*(its + (it - itb)) = *it;
		++it;
	}


	while (chunk > 1) { //sorting loop
		itb = this->_qcur->begin();
		ite = this->_qcur->end();
		its = this->_qswap->begin();
		chunk /= 2;
		it = itb + chunk;
		int i = (ite-itb)/chunk;
		it2 = its + (i/2 + i%2) * chunk;
		while (it + chunk <= ite) { //put large element in swap vector 
			for (int j = 0; j < chunk; ++j) 
				*(it2 + j) = *(it + j);
			it += 2 * chunk;
			it2 += chunk;
		}
		//do small element
		it2 = its + (i/2 + i%2) * chunk - 1; //were the search begin
		for (i = 0; i < chunk; ++i) { // first one is alway free
			*it2 = *(itb + chunk - 1 - i);
			--it2;
		}
		int jac = 0; //jacobsthal number - 1
		it = itb + 5*chunk - 1; //element to swap
		if (it >= ite) it -= 2 * chunk;
		int maxsearch = 2;
		while (it2 >= its) { //insert current chunk size
			if (it == itb + chunk - 1 + jac * 2 * chunk) { //advance the jacosthal
				jac = 2*jac + 2 - (jac&3);
				it = itb + chunk - 1 + (2*jac + 2 - (jac&3)) * 2 * chunk;
				while (it >= ite) it -= 2*chunk;
				maxsearch *= 2;
			}
			int insert = 0;
			for (int j = maxsearch; j > 0; j = j >> 1) { //search were to insert
				if (it2 + chunk * (insert + j) < this->_qswap->end() && *it > *(it2 + chunk * (insert + j)))
					insert += j;
			}
			for (int j = 0; j < chunk; ++j){ //put the element at the right place
				for (int k = 0; k < insert; ++k)
					*(it2 + k*chunk) = *(it2 + k*chunk + chunk);
				*(it2 + insert*chunk) = *it;
				--it;
				--it2;
			}
			it -= chunk;
		}
		swap(this->_cur, this->_swap);
	}
}

void PmergeMe::sort() {
	clock_t start, end;
	double time;
	std::cout << "Before: " << *(this->_cur) << std::endl;
	start = clock();
	this->sortVec();
	end = clock();
	time = ((double) (end - start) / CLOCKS_PER_SEC * 1000000.0);
	start = clock();
	this->sortQue();
	end = clock();
	std::cout << "After:  " << *(this->_cur) << std::endl;
	std::cout << "Time to process a range of " << this->_cur->size() << " elements with std::vector : " << time << " us" << std::endl;
	time = ((double) (end - start) / CLOCKS_PER_SEC * 1000000.0);
	std::cout << "Time to process a range of " << this->_cur->size() << " elements with std::deque : " << time << " us" << std::endl;
}
