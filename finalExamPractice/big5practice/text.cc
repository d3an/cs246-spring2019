#include "text.h"
#include <iostream>
using namespace std;

// Default Constructor
Text::Text(const string &title, const string &author, int length, const string &topic):
  AbstractBook{title, author, length}, topic{topic} {}

// Copy Constructor
Text::Text(const Text &other) : AbstractBook{other}, topic{other.topic} {
	cout << "Running Text's copy ctor..." << endl;
}

// Move Constructor
Text::Text(Text && other) : AbstractBook{std::move(other)}, topic{std::move(other.topic)} {
	cout << "Running Text's move ctor..." << endl;
}

// Copy Assignment Operator
Text & Text::operator=(const Text & rhs) {
	cout << "Running Text's copy assignment operator..." << endl;

	if (this == &rhs) return *this;
	AbstractBook::operator=(rhs);
	topic = rhs.topic;
	return *this;
}

// Move Assignment Operator
Text & Text::operator=(Text && rhs) {
	cout << "Running Text's move assignment operator..." << endl;

	if (this == &rhs) return *this;
	AbstractBook::operator=(std::move(rhs));
	topic = std::move(rhs.topic);
	return *this;
}

bool Text::isHeavy() const { return getLength() > 500; }
string Text::getTopic() const { return topic; }

// My favourite textbooks are C++ books
bool Text::favourite() const { return topic == "C++"; }

// Destructor
Text::~Text() {}
