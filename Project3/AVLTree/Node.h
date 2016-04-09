#pragma once
#include <limits>

static const int INVALID_NUM = std::numeric_limits<int>::max();
static const size_t INVALID_NODE = std::numeric_limits<size_t>::max();


// Struct that contains the data pair
// A key should not be constructed without its value
struct DataPair {
	DataPair(const int key, const int value) : key_(key), value_(value){}
	int key_, value_;
};

class Node {
public:

	// Empty Constructor
	Node() : data_(INVALID_NUM, INVALID_NUM), position_( INVALID_NODE ) {
		setPointers(INVALID_NODE, INVALID_NODE, INVALID_NODE);
	}

	// Parameterized Constructor
	Node(const int key, const int value) : data_(key,value) {
		setPointers(INVALID_NODE, INVALID_NODE, INVALID_NODE);
	}

	void setPointers(size_t p, size_t lc, size_t rs) {
		parent_ = p;
		leftChild_ = lc;
		rightChild_ = rs;
	}

	void clear() {
		data_.key_ = INVALID_NUM;
		data_.value_ = INVALID_NUM;
		setPointers(INVALID_NODE, INVALID_NODE, INVALID_NODE);
	}

	// Public Members
	DataPair data_;
	size_t parent_, leftChild_, rightChild_, position_;
};
