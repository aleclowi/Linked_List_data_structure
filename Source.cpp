#include "List.h"
#include<iostream>
int main() {
	// uses initialzier list constructor
	pic10b::LinkedList list0{ 2,4,6,8 };
	list0.push_front(0);
	list0.push_front(-11);
	list0.pop_front();

	for (int i : list0) { // for all the ints, print them
		std::cout << i << " ";
	}
	std::cout << '\n';
	pic10b::LinkedList list1; // default constructor
	list1.push_back(8);
	list1.push_back(3);
	list1.push_back(14);
	list1.push_back(-13);
	list1.push_back(0);
	list1.push_back(3); // a second 3!!!
	auto it = list1.begin();
	++it;
	
	list1.insert(it, 144);
	list1.insert(list1.end(), 44);
	list1.pop_back();
	const pic10b::LinkedList list2 = list1;
	list1.sort();
	std::cout << "List 1: " << list1 << '\n';
	std::cout << "List 2: " << list2 << '\n';
	auto beg1 = list1.begin();
	auto end1 = list1.end();
	end1--; // so it last element will not be searched through in the searche to come...
	auto beg2 = list2.begin();
	auto end2 = list2.end();
	bool found1 = pic10b::seqSearch(beg1, end1, 144);
	bool found2 = pic10b::seqSearch(beg2, end2, 144);
	// the boolalpha turns the 0/1 for false/true into "false" and "true"
	std::cout << std::boolalpha << found1 << " " << found2 << '\n';
	return 0;
}
