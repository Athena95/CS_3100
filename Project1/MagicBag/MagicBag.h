#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>

using namespace std;

// Defines default bag size for the MagicBag
static const int DEFAULT_CAPACITY = 20;

template< class T > class MagicBag
{
public:
	// Empty Constructor
	MagicBag() : capacity(DEFAULT_CAPACITY), size(0) { 
		bag = new T[capacity];
	}

	// Equals Operator Overloading Function
	MagicBag& operator=(const MagicBag& other) {
		// Set all other's members to this's members
		capacity = other.capacity;
		size = other.size;
		bag = new T[capacity];

		// Copy all elements from other's bag to this bag
		copyThisBag(this->bag, other.bag, size);
		return *this;
	}

	// Copy Constructor
	MagicBag(const MagicBag& other) {
		*this = other;
	}

	// Destructor
	~MagicBag() {
		delete[] bag;
	}

	// Public Functions
	// Draws and removes a random item from the bag
	T draw() {
		// Throw exception and abort if there are no items to draw
		// We do not want to continue with bad data--better to just quit
		try {
			if (size == 0) 
				throw(std::out_of_range(0));
		}
		catch ( std::exception& e ) {
			cerr << __FILE__ << " line " << __LINE__ << endl;
			cerr << "ERROR: there are no items to draw from the bag";
			abort();
		}

		// Generate random number
		srand((unsigned int)time(nullptr));
		int num = rand() % size + 1;

		T item = bag[num - 1];			// Get item at random position
		bag[num - 1] = bag[size - 1];	// Move the last item to the position of the removed item
		size--;							// Reduce size

		return item;
	}

	// Returns the occurence of an item in the bag
	int peek(T item) {
		// Iterate through bag to find occurrence of item
		int count = 0;
		for (size_t i = 0; i < size; ++i) {
			if (bag[i] == item) {
				count++;
			}
		}
		return count;
	}

	// Inserts an item at the end of the array
	// Resizes the array if capacity is full
	void insert(T item) {
		// Resize bag to twice its original size if the bag is full
		if (size == capacity) {
			resizeBag(capacity * 2);
		}

		bag[size] = item;		// Add item to end of array
		size++;					// Increase size by 1
	}

private:
	//Private Members
	T* bag;
	int capacity, size;

	// Private Functions
	// Resizes the bag, given a new size
	void resizeBag(int newCapacity) {
		capacity = newCapacity;							// Set capacity to the new capacity
		T* newBag = new T[newCapacity];					// Create new bag with given capacity
		copyThisBag(newBag, this->bag, this->size);		// Copy the elements from old array to new array
		this->bag = newBag;								// Set new bag to this instance of MagicBag's bag
	}

	// Copies the contents from bag1 to bag0
	// @param size is the size of bag1 (the bag to be copied)
	void copyThisBag( T bag0[], const T bag1[], int size ) {
		for (size_t i = 0; i < size; ++i) {
			bag0[i] = bag1[i];
		}
	}

	// Stream Operator Overload
	// Allows the MagicBag to be printed in "[ item1 item2 item3 [...] ]" format
	friend ostream& operator<<(ostream& os, const MagicBag& mb) {
		os << "[ ";
		for (size_t i = 0; i < mb.size; ++i) {
			os << mb.bag[i] << " ";
		}
		os << "]";

		return os;
	}
};