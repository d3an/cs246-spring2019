#ifndef _ABSTRACTBOOK_H_
#define _ABSTRACTBOOK_H_
#include <string>

class AbstractBook {
	std::string title, author;
	int length;

protected:
	int getLength() const;

public:
	AbstractBook(const std::string &title, const std::string &author, int length);
	AbstractBook(const AbstractBook &b);
	AbstractBook(AbstractBook && b);
	virtual AbstractBook & operator=(const AbstractBook & rhs);
	virtual AbstractBook & operator=(AbstractBook && rhs);

	std::string getTitle() const;
  	std::string getAuthor() const;
  	virtual bool isHeavy() const;

  	virtual bool favourite() const;

  	virtual ~AbstractBook() = 0;
};

#endif
