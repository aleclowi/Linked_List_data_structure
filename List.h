#ifndef _LIST_
#define _LIST_

#include <iostream>
#include <utility>
#include <stdexcept>

/*namespace intList {
class node; // declare the node
class iterator; // declare a normal iterator
class const_iterator; // declare an iterator to work on const LinkedLists
class LinkedList{
friend iterator; // iterators need to know first element
friend const_iterator;
friend void swap(LinkedList&, LinkedList&); // to swap two LinkedLists
*/
namespace pic10b
{

	class LinkedList; class iterator; class const_iterator; class node;
	/**
	@LinkedList class to store ints and some helper functions with everything written in the pic10b namespace.
	Code should not have any memory leaks due to the leak checker
	*/
	class LinkedList
	{
		friend iterator; // iterators need to know first element
		friend const_iterator;
		friend void swap(LinkedList& one, LinkedList& another); // to swap two LinkedLists
	public:

		/**
		Default constructor: This default constructor is empty

		@param none
		*/
		LinkedList() noexcept;


		/**
		This constructor takes an initializer list and begins by storing those items

		@param accepts an initializer list
		*/
		LinkedList(std::initializer_list<int> list);


		/**
		Copy construtor: creating a newly constructed object into a copy of another

		@param accepts constructor reference
		*/
		LinkedList(const LinkedList& copy);

		/**
		Move constructor: able to modify the value of the object

		@param accepts constructor reference
		*/
		LinkedList(LinkedList&& copy) noexcept : LinkedList()
		{
			swap(*this, copy);
		}

		LinkedList& operator=(LinkedList& L);
		LinkedList& operator=(LinkedList&& L) noexcept; //move assignment

		/**
		Destructor: clears up all of the object resources

		@param none
		*/
		~LinkedList();


		/**
		This function accepts an int that adds the int to the end of the list (appends)

		@param the int to be added
		@return type void, modifies the initializer list
		*/
		void push_back(int val);

		/**
		This function pops off an element at the end and throws exception if the list is empty

		@param requires call from the class, doesn't accept a value
		@return type void, modifies the initializer list
		*/
		void pop_back();

		/**
		This function prepends an int at the beginning

		@param accepts a certain int that will be added to the beginning of the list
		@return type void, modifies the intializer list
		*/
		void push_front(int val);

		/**
		This function removes an int at the beginning

		@param accepts a certain int that will be added to the beginning of the list
		@return type void, modifies the intializer list
		*/
		void pop_front();

		/**
		This function returns iterators to the beginning;

		@param requires call from the class, doesn't accept a value
		@return type void, modifies the initializer list
		*/
		iterator begin();

		/**
		This function returns iterators to the end;

		@param requires call from the class, doesn't accept a value
		@return type void, modifies the initializer list
		*/
		iterator end();

		/**
		This CONST OVERLOADED function returns iterators to the beginning;

		@param requires call from the class, doesn't accept a value
		@return type void, modifies the initializer list
		*/
		const_iterator begin() const;

		/**
		This CONST OVERLOADED function returns iterators to the end;

		@param requires call from the class, doesn't accept a value
		@return type void, modifies the initializer list
		*/
		const_iterator end() const;

		/**
		This function accepts an interator and value to insert, with the value being inserted
		before the point where the iterator points;


		@param an iterator and a value to insert
		@return type void, modifies the initializer list
		*/
		void insert(iterator itr, int val);

		/**
		This function accepts an iteratorand removing the pointed - to element

		@param an iterator
		@return type void, modifies the initializer list
		*/

		void erase(iterator itr); // erase value at position

		/**
		This function returns the size of the list, same way as .size()

		@param none
		@return returns an int value of the size of the intializer list
		*/
		size_t size() const;

		/**
		This function sorts the elements in ascending order from beginning to end

		@param none
		@return returns an int value of the size of the initializer list
		*/

		void sort();

		/**
		overloaded stream operator << output in the desired format of the square

		@param an output stream and MagicSquare class object
		@return outputs the desired square format
		*/

		friend std::ostream& operator<<(std::ostream& os, const LinkedList& c);

	private:
		node* first, * last;
		size_t sz;
	};


	class iterator
	{
		// LinkedList may change data of iterator during operations
		friend LinkedList;
	public:

		iterator& operator++(); // prefix ++
		iterator operator++(int x); // postfix ++
		iterator& operator--(); // prefix - -
		iterator operator--(int x); // postfix - -
		int& operator*() const; // dereferencing operator (unary)
		friend bool operator==(const iterator& left, const iterator& right); //declar these operators as friend
		operator const_iterator() const; //conversion operator to convert from iterator to const_iterator
	private:
		node* curr; // currently managed node
		const LinkedList* container; // the iterator should not change the list
		// constructor: requires a node and list to point to
		iterator(node* n, const LinkedList* ell) : curr(n), container(ell) {}
	};

	class const_iterator // declare an iterator to work on const LinkedLists
	{
		// LinkedList may change data of iterator during operations
		friend LinkedList;
	public:
		const_iterator& operator++(); // prefix ++
		const_iterator operator++(int x); // postfix ++
		const_iterator& operator--(); // prefix - -
		const_iterator operator--(int x); // postfix - -
		int& operator*() const; // dereferencing operator (unary)
		friend bool operator==(const const_iterator& left, const const_iterator& right); // comparison
		//friend bool seqSearch(const_iterator& citr1, const_iterator& citr2, const int& x);
		friend iterator::operator const_iterator() const; //conversion operator
	private:
		node* curr; // currently managed node
		const LinkedList* container; // the iterator should not change the list
		// constructor: requires a node and list to point to
		const_iterator(node* n, const LinkedList* ell) : curr(n), container(ell) {}
	};

	class node
	{
		friend LinkedList; /* LinkedList needs to construct nodes and to
		know next/prev of node for insertions, deletions, etc. */
		friend iterator; // iterators need to know next/prev to move, etc.
		friend const_iterator;
		friend std::ostream& operator<<(std::ostream& os, const LinkedList& c);
	private:
		int val; // the data
		node* prev, * next; // previous and next nodes
		node(int _val) : val(_val), prev(nullptr), next(nullptr) {}
	};

	/**
		This function seqSearch searches over the range provided by the iterators
		from the first up to but not including the second iterator.

		@param two const_irerators and a value
		@return returns true or false if the sought value is found.
		*/

	bool seqSearch(const const_iterator& citr1, const const_iterator& citr2, const int& x);
	
	std::ostream& operator<<(std::ostream& os, const LinkedList& c); //overloaded operator redeclared outside of class since it is declared as friend

	/**
	overloaded == operator to work for iterators

	@param a left iterator and a right iterator
	@return outputs true when the iterators are equal and false when they are not equal
	*/

	bool operator==(const iterator& left, const iterator& right);

	/**
	overloaded == operator FOR CONST_ITERATOR to work for iterators

	@param a left iterator and a right iterator
	@return outputs true when the iterators are equal and false when they are not equal
	*/

	bool operator==(const const_iterator& left, const const_iterator& right);

	/**
	overloaded != operator to work for iterators

	@param a left iterator and a right iterator
	@return outputs true when the iterators are not equal and false otherwise
	*/

	bool operator!=(const iterator& left, const iterator& right);

	/**
	overloaded != operator FOR CONST_ITERATOR to work for iterators

	@param a left iterator and a right iterator
	@return outputs true when the iterators are not equal and false otherwise
	*/

	bool operator!=(const const_iterator& left, const const_iterator& right);
};

#endif