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
Text & Text::operator=(const AbstractBook & rhs) {
	cout << "Running Text's copy assignment operator..." << endl;

	const Text & t = dynamic_cast<const Text &>(rhs);
	AbstractBook::operator=(t);
	topic = t.getTopic();
	return *this;
}

// Move Assignment Operator
Text & Text::operator=(AbstractBook && rhs) {
	cout << "Running Text's move assignment operator..." << endl;

	const Text & t = dynamic_cast<const Text &>(rhs);
	AbstractBook::operator=(std::move(t));
	topic = t.getTopic();
	return *this;
}

bool Text::isHeavy() const { return getLength() > 500; }
string Text::getTopic() const { return topic; }

// My favourite textbooks are C++ books
bool Text::favourite() const { return topic == "C++"; }

// Destructor
Text::~Text() {}
