#ifndef _ABSTRACTBOOK_H_
#define _ABSTRACTBOOK_H_
#include <string>

class AbstractBook {
	std::string title, author;
	int length;

protected:
	int getLength() const;
	AbstractBook & operator=(const AbstractBook & rhs);
	AbstractBook & operator=(AbstractBook && rhs);

public:
	AbstractBook(const std::string &title, const std::string &author, int length);
	AbstractBook(const AbstractBook &b);
	AbstractBook(AbstractBook && b);

	std::string getTitle() const;
  	std::string getAuthor() const;
  	virtual bool isHeavy() const;

  	virtual bool favourite() const;

  	virtual ~AbstractBook() = 0;
};

#endif
