

# Lecture 17

## Inheritance, Virtual Functions

### Last Time

![UML_6](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/UML_6.jpg)

- A derived class inherits all members from the base class
- A derived class cannot access private inherited members

```cpp
class Book {
	string title, author;
	int numPages;
	public:
	Book(string, string, int);
};

class Comic : public Book {
  string hero;
  public:
  ...;
};

class Text : public Book {
  string topic;
  public:
  ...;
};
```

```cpp
Text::Text(string t, string a, int n, string topic) : 
	title{t}, author{a}, numPages{n}, topic{topic} {}
// Won't work because:
// (1) Inherited fields were private
// (2) MIL can only use fields declared by the class
// (3) No default constructor for Book *
```

### 4 Steps to Object Construction

1. Space is allocated
2. Superclass part is constructed
3. Subclass field constructed
4. Constructor body runs

```cpp
Text::Text(string t, string a, int n, string topic) :
	Book{t, a, n}, topic{topic} {}
```

### Protected

If a member is "protected" it is accessible by the class of its subclasses

```cpp
class Book {
	protected:
  string title, author;
  int numPages;
  public:
  ...;
};

void Text::addAuthor(string a) {
  author += a; // Ok since author is protected
}

int main() {
  Text t = ...;
  t.author = ...; // Invalid
}
```

### Protected breaks encapsulation

**Advice:** Keep fields private

- provide protected accessors/mutators
- UML: #protected



### Method Overwriting

`isHeavy()?`

- Book	isHeavy	numPages > 200
- Text      isHeavy    numPages > 500
- Comic  isHeavy    numPages > 30

```cpp
class Book {
	int numPages;
  public:
  int getNumPages() const { return numPages; }
  bool isHeavy() const { return numPages > 200; }
};

bool Text::isHeavy() const { return getNumPages() > 500; }
bool Comic::isHeavy() const { return getNumPages() > 30; }

Book b{..., ...,  50};
b.isHeavy(); // Book.isHeavy, false

Comic c{..., ..., 40, "batman"};
c.isHeavy(); // Comic::isHeavy, true

Book b1 = Comic{..., ..., 40, "batman"}; // Calls Book's copy constructor
b1.isHeavy(); // Book::isHeavy, false => Good 
// Comic::isHeavy, true => Bad
```



![UML_7](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/UML_7.jpg)

Using superclass pointers, to point to subclass objects will not cause slicing.

```cpp
Comic c{..., ..., 40, "Batman"};
Book *bp{&c};
bp->isHeavy();
// (1) Book::isHeavy()
// (2) Comic::isHeavy()
```

![UML_8](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/UML_8.jpg)

By default, the compiler looks at the declared type of the pointer to choose which method to run (static dispatch). We typically want the method to be chosen based on the type of object. 

### Use "virtual" keyword

```cpp
class Book {
	...;
	public:
  virtual bool isHeavy() const { ...; }
};

bool Text::isHeavy() const override { ...; }
bool Comic::isHeavy() const override { ...; }

Comic c{..., ..., 40, ...};
Comic *cp{&c};
Book *bp{&c};
Book &br{c};

// Comic::isHeavy runs for all three
cp->isHeavy();
bp->isHeavy();
br.isHeavy();
```

![UML_9](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/UML_9.jpg)



### Virtual Method

The choice of method is based on the runtime type of the object.

### DYNAMIC DISPATCH

- More costly than static dispatch

```cpp
Book *collection[20];
// ...
for (int i = 0; i < 20; ++i) {
	collection[i]->isHeavy();
}
```

**Polymorphism:** the ability to accommodate multiple types within one abstraction

```cpp
istream & operator>>(istream &, ...); 
// cin >> x;
// ifstream f{...};
// f >> x;
// ifstream IS-A istream
```

### Destructors (4 steps to destroying objects)

1. Subclass destructor runs
2. Destructor for subclass fields that are objects
3. Superclass destructor runs
4. Space is reclaimed

#### Examples

```cpp
class x {
	int *x;
	x(int m) : x{ new int[m] } {}
  ~x() { delete[] x; }
};

class y : public X {
  int *y;
  y(int m, int n) : x{m}, y{ new int[n] } {}
  ~y() { delete[] y; }
};

x *myEx = new y{10,20};
delete myEx; // Leaks memory
// ~y is never called:
//	Advice: All classes that can be subclassed should have a virtual destructor
```

