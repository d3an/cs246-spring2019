#include "abstractbook.h"
#include <iostream>
using namespace std;

// Default Constructor
AbstractBook::AbstractBook(const string &title, const string &author, int length) :
  	title{title}, author{author}, length{length} {}

// Copy Constructor
AbstractBook::AbstractBook(const AbstractBook &b) : title{b.title}, author{b.author}, length{b.length} {
  	cout << "Running AbstractBook's copy ctor... " << endl;
}

// Move Constructor
AbstractBook::AbstractBook(AbstractBook && b) : title{std::move(b.title)}, author{std::move(b.author)}, length{std::move(b.length)} {
	cout << "Running AbstractBook's move ctor..." << endl;
}

// Copy Assignment Operator
AbstractBook & AbstractBook::operator=(const AbstractBook &rhs) {
	cout << "AbstractBook copy assignment operator running ..." << endl;

	if (this == &rhs) return *this;
	title = rhs.title;
	author = rhs.author;
	length = rhs.length;
	return *this;
}

// Move Assignment Operator
AbstractBook & AbstractBook::operator=(AbstractBook && rhs) {
	cout << "AbstractBook move assignment operator running ..." << endl;

	if (this == &rhs) return *this;
	title = std::move(rhs.title);
	author = std::move(rhs.author);
	length = std::move(rhs.length);
	return *this;
}

int AbstractBook::getLength() const { return length; }
string AbstractBook::getTitle() const { return title; }
string AbstractBook::getAuthor() const { return author; }
bool AbstractBook::isHeavy() const { return length > 200; }

// My favourite books are short books.
bool AbstractBook::favourite() const { return length < 100; }

// Destructor
AbstractBook::~AbstractBook() {}
