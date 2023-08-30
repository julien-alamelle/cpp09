#pragma once
#include <vector>
#include <deque>

class PmergeMe {
private:
	std::vector<int>		_tab;
	std::vector<int>		_tab2;
	std::vector<int>*		_cur;
	std::vector<int>*		_swap;
	std::deque<int>			_que;
	std::deque<int>			_que2;
	std::deque<int>*		_qcur;
	std::deque<int>*		_qswap;

	void sortVec();
	void sortQue();

public:
	PmergeMe();
	PmergeMe(const PmergeMe &);
	virtual ~PmergeMe();
	PmergeMe&	operator=(const PmergeMe &);

	void insert(int i);
	void sort();
};
