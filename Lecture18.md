# Lecture 18

## Abstract Classes, Templates, Exceptions

### Last time: Destructors

```cpp
class x {
	...;
  virtual ~x() {...;}
};

class y : public x {
  ...;
  ~y(){...;}
};

x * myX = new y(...);
delete myX;
```

If a class will never have a subclass, declare it final.

```cpp
class y final : public x {
	...;
};
```



```cpp
class Student {
	...;
	public:
	virtual int fees() = 0; // Pure virtual method
};

class regular : public Student {
  ...;
  public:
  int fees() override {...;}
};

class coop : public Student {
  ...;
  public:
  int fees() override {...;}
};
```

`Student::fees()` has no implementation.

- We don't want to implement it
- Make it Pure Virtual (P.V.)

**Virtual:** subclasses ***may*** override behaviour

**PV:** subclasses ***must*** implement method to be ***CONCRETE***

Student has a PV method:

- It is incomplete
- It is an ABSTRACT class

A class is abstract if:

- It declares a PV method
- It inherits PV method(s) that it does not implement

A class is concrete if it is not abstract. Cannot create objects of an abstract class. `Student s; // bad`

### Abstract Classes

- organize subclasses
- members (fields/methods) that are common across all subclasses can be placed in the base class
- act as an interface
- Polymorphism

![CODE_1](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/CODE_1.jpg)

![CODE_2](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/CODE_2.jpg)



### C++ Templates

```cpp
template <typename T>

class Stack {
	int len;
  int cap;
  T * contents;
  public:
  void push T;
  void pop(void);
  T top();
  ~Stack();
};
```

C++ template class is a class parameterized on a type.

```cpp
Stack<int> s1;
s1.push(1);

Stack<string> s2;
s2.push("hello");
```

#### Template List Class

```cpp
template <typename T>

class List {
	struct Node {
		T data;
		Node *next;
	};
  Node * theList = nullptr;
  public:
  class Iterator {
    Node * cur;
    explicit Iterator(...;) : ...;
    public:
    T &operator*() {...}
    Iterator &operator++() {...}
    bool operator!=(...) {...}
    friend class List<T>;
  };
  T &ith(int i);
  void addToFront(T &t);
  ~List();
};
```

```cpp
List<int> l1;
l1.addToFront(1);
l1.addToFront(2);

List<List<int>> l2;
l2.addToFront(l1);
```

### Standard Template Library (STL)

`std::vector` `#include <vector>`

- template class
- dynamic length arrays
  - heap allocated
  - automatically resize as needed

```cpp
vector<int> v{3,4}; // [3,4]
v.emplace_back(5); // [3,4,5]
v.pop_back(); // [3,4]
for (int i = 0; i < v.size(); ++i) {
	cout << v[i] << endl;
}
for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
  cout << *it << endl;
}
for (auto n : v) {
  cout << n << endl;
}
for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
  cout << *it << endl;
}

v.erase(v.begin());
v.erase(v.endl() - 1);
```

```cpp
v[i] // unchecked access
v.at(i) // checked access
```

If `i` is not in range, `out_of_range` exception is thrown

`lectures/c++/exceptions`

- `rangeError.cc`
- `rangeErrorCaught.cc`
  - After an exception is caught, program continues after the catch block.
- `callChain.cc`

**Stack unwinding:** When an exception occurs, the call stack is repeatedly popped until an appropriate catch block is found.

