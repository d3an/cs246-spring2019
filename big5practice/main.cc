#include "text.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	Text t1("Programming for Beginners", "Niklaus Wirth", 200, "BASIC");
  	Text t2("Programming for Big Kids", "Bjarne Stroustrup", 300, "C++");

  	// t1 = t2;
  	Text t3{ t2 };
  	// cout << "Book 1: " << t1.getTitle() << ", " << t1.getAuthor() << ", " << t1.getTopic() << endl;
  	cout << "Book 2: " << t2.getTitle() << ", " << t2.getAuthor() << ", " << t2.getTopic() << endl;
  	cout << "Book 3: " << t3.getTitle() << ", " << t3.getAuthor() << ", " << t3.getTopic() << endl;

}
