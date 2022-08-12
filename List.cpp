#include <iostream>
#include <utility>
#include <stdexcept>

#include "List.h"

using namespace pic10b;

LinkedList::LinkedList() noexcept : first(nullptr), last(nullptr)
{}

LinkedList::LinkedList(std::initializer_list<int> list) : first(nullptr), last(nullptr)
{
	for (int i : list)
	{ // take each value from rhs
		push_back(i);
	}
}

// copy constructor : copy elements over one by one
LinkedList::LinkedList(const LinkedList& copy) : first(nullptr), last(nullptr)
{
	node* n = copy.first; //create a copy of the first node
	//while its not null
	while (n != nullptr) 
	{
		push_back(n->val);//member pushback the value
		n = n->next;//move on to the next
	}
}

LinkedList& LinkedList::operator=(LinkedList& L)
{
	swap(*this, L); //copy assignment just swapping 
	return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& L) noexcept
{
	std::swap(*this, L);//move assignment just swapping then setting first and last to null
	L.first = nullptr;
	L.last = nullptr;
	return *this;
}

LinkedList::~LinkedList()
{
	node* n = first; // start at first node
	while (n != nullptr)
	{ // while not past the end denoted by nullptr
		node* temp = n->next; // temporarily store the next position
		delete n; // delete the node on heap
		n = temp; // move n right
	}
}

void LinkedList::push_back(int val)
{
	node* n = new node(val); // create a new node
	if (last)
	{ // if last node not null
		last->next = n; // make last point to n
		n->prev = last; // make n have last as its previous
		last = n; // update the last position
	}
	else
	{ // in this case the last node is null so list is empty
		first = last = n; // both equal to n
	}
}

void LinkedList::pop_back()
{
	if (!last)
	{ // list is empty if last null
		throw std::logic_error("pop back on empty list");
	}
	else if (first == last)
	{ // if just one element
		delete first; // free heap memory
		first = last = nullptr; // make both null because empty again
	}
	else
	{ // many elements
		node* newlast = last->prev; // store the new last node
		newlast->next = nullptr; // set its next pointer to null
		delete last; // free the heap memory
		last = newlast; // update the last value
	}
}

void LinkedList::push_front(int val)
{
	node* n = new node(val); // create a new node
	if (first)
	{ // if first node not null
		first->prev = n; // make first point to n
		n->next = first; // make n have first as its previous
		first = n; // update the first position
	}
	else
	{ // in this case the first node is null so list is empty
		first = last = n; // both equal to n
	}
}

void LinkedList::pop_front()
{
	if (!first)
	{ // list is empty if first null
		throw std::logic_error("pop front on empty list");
	}
	else if (first == last)
	{ // if just one element
		delete first; // free heap memory
		first = last = nullptr; // make both null because empty again
	}
	else
	{ // many elements
		node* newfirst = first->next; // store the new first node
		newfirst->prev = nullptr; // set its prev pointer to null
		delete first; // free the heap memory
		first = newfirst; // update the first value
	}
}

iterator LinkedList::begin()
{ // return type requires scope
	if (first == nullptr) 
	{//empty list
		throw std::logic_error("list is empty");
	}
	return iterator(first, this); // return iterator for node of smallest value
}
// end iterator means “past the end” and should store null
iterator LinkedList::end()
{
	if (first == nullptr) { //empty list
		throw std::logic_error("list is empty");
	}
	//not empty
	return iterator(nullptr, this);
}

const_iterator LinkedList::begin() const
{ // return type requires scope
	if (first == nullptr) {//empty list
		throw std::logic_error("list is empty");
	}
	return const_iterator(first, this); // return iterator for node of smallest value
}
// end iterator means “past the end” and should store null
const_iterator LinkedList::end() const
{
	if (first == nullptr) { //empty list
		throw std::logic_error("list is empty");
	}
	//not empty
	return const_iterator(nullptr, this);
}

void LinkedList::insert(iterator itr, int val)
{
	if (itr.curr == nullptr)
	{ // then inserting before past-the-end
		push_back(val);
	}
	else if (itr.curr == first)
	{ // then at beginning
		push_front(val);
	}
	else
	{ // then in middle
		node* n = new node(val); // create new node
		n->next = itr.curr; // set n’s next
		n->prev = itr.curr->prev; // set n’s previous
		itr.curr->prev->next = n; // make current previous’ next node into n
		itr.curr->prev = n; // make current previous node into n
	}
}

void LinkedList::erase(iterator itr)
{
	if (itr.curr == first)
	{ // removing first
		pop_front(); // remove first
	}
	else if (itr.curr == last)
	{ // removing last
		pop_back(); // remove last
	}
	else
	{ // somewhere in the middle
		itr.curr->prev->next = itr.curr->next; // reroute next of previous
		itr.curr->next->prev = itr.curr->prev; // reroute previous of next
		delete itr.curr; // free the heap memory of item being removed
	}
}

size_t LinkedList::size() const
{
	size_t sz = 0;
	node* n = first; //create a new node pointed to first
	while (n != nullptr) 
	{
		sz++; //increment size
		n = n->next; // go to the next element
	}
	delete n;
	return sz; //return number of elements
}


void LinkedList::sort()
{
	//create a variable of the first node
	auto fir = first;
	//while the first node is not null
	while (fir != nullptr) 
	{
		node* sm = fir;
		auto n = fir->next; //move to the next
		while (n != nullptr) //while the next node is also not null
		{
			if (n->val < sm->val) //check the two values, if the one behind is greater then swap then
			{
				sm = n;
			}
			n = n->next;
		}
		std::swap(sm->val, fir->val); //swapping here
		fir = fir->next; //move to the next node then loop will run over again
	}
	delete fir; // delete the node on the heap
}

bool pic10b::seqSearch(const const_iterator& citr1, const const_iterator& citr2, const int& x)
{
	//const iterator loop starting at the first iterator entered, moving to the second iterator entered
	for (const_iterator n = citr1; n != citr2; n++)
	{
		if (*n == x) //if the referenced iterator is found, return true
		{
			return true;
		}
	}
	return false; //false otherwise
}

iterator::operator const_iterator() const //conversion operator
{
	//create a new const_iter using the iter parameters
	const_iterator copy(curr, container);
	return copy;
}

iterator& iterator::operator++()
{
	if (curr == container->last->next) 
	{ // cannot go after last
		throw std::logic_error("Invalid address");
	}
	else 
	{ // in the middle somewhere
		curr = curr->next; // reference next node
	}
	return *this;
}
iterator iterator::operator++(int x)
{
	iterator copy(*this);
	++(*this); // or this->operator--();
	return copy;
}

iterator& iterator::operator--()
{
	if (curr == container->first)
	{ // cannot go before first
		throw std::logic_error("Invalid address");
	}
	else if (curr == nullptr)
	{ // just past the end, go to last
		curr = container->last; // now make iterator refer to last element
	}
	else 
	{ // in the middle somewhere
		curr = curr->prev; // reference previous node
	}
	return *this;
}
iterator iterator::operator--(int x)
{
	iterator copy(*this);
	--(*this); // or this->operator--();
	return copy;
}

int& iterator::operator*() const
{
	return curr->val; // return reference to the int stored
}


const_iterator& const_iterator::operator++()
{
	if (curr == container->last || curr == nullptr) { // cannot go after last
		throw std::logic_error("Invalid address");
	}
	else { // in the middle somewhere
		curr = curr->next; // reference next node
	}
	return *this;
}
const_iterator const_iterator::operator++(int x)
{
	const_iterator copy(*this);
	++(*this); // or this->operator--();
	return copy;
}// postfix ++
const_iterator& const_iterator::operator--()
{
	if (curr == container->first)
	{ // cannot go before first
		throw std::logic_error("Invalid address");
	}
	else if (curr == nullptr)
	{ // just past the end, go to last
		curr = container->last; // now make iterator refer to last element
	}
	else { // in the middle somewhere
		curr = curr->prev; // reference previous node
	}
	return *this;
}// prefix - -
const_iterator const_iterator::operator--(int x)
{
	const_iterator copy(*this);
	--(*this); // or this->operator--();
	return copy;
}// postfix - -
int& const_iterator::operator*() const
{
	return curr->val; // return reference to the int stored
}// dereferencing operator (unary)


bool pic10b::operator==(const iterator& left, const iterator& right)
{//here just return the equals result
	return ((left.curr == right.curr) && (left.container == right.container));
}
// != defined by negating ==
bool pic10b::operator!=(const iterator& left, const iterator& right)
{
	return !(left == right);
}

bool pic10b::operator==(const const_iterator& left, const const_iterator& right)
{//here just return the equals result
	return ((left.curr == right.curr) && (left.container == right.container));
}
// != defined by negating ==
bool pic10b::operator!=(const const_iterator& left, const const_iterator& right)
{
	return !(left == right);
}
void pic10b::swap(LinkedList& one, LinkedList& another)
{
	std::swap(one.first, another.first);
	std::swap(one.last, another.last);
}
std::ostream& pic10b::operator<<(std::ostream& os, const LinkedList& c)
{
	//create a node that will point to the first element
	//os << c.vals;
	node* temp = c.first;
	if (c.first == nullptr) 
	{ // the list is empty
		throw std::logic_error("Empty List");
	}
	//while loop, so long as the first element is not empt
	while (temp != nullptr)
	{
		//print the value
		os << temp->val << " ";
		temp = temp->next;//move on the next one, do it over again
	}
	delete temp;
	return os; //return the stream
}