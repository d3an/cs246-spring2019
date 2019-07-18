# Lecture 15

## Iterator Design Pattern, Short Topics

### Last Time

```cpp
class List {
	struct Node;
  Node *theList = nullptr;
  public:
  void addToFront(int);
  int ith(int);
  ~List();
};
```

**Problem:** List traversal is $O(n^2)$.

Solution: 

```cpp
class List {
  Node * theList;
  Node * curr;
  public:
  void reset();
  int &getNextVal();
};

Node * curr = theList;
while (curr) {
	...;
	curr = curr->next;
}
```



### Iterator Design Pattern

- Good solutions to common design problems
- Keep track of how much of the list we have traversed

```cpp
for (int *p = arr; p != arr+size; ++p) {
	... *p ...;
}
```

We will create a new class (Iterator) that acts as a pointer into a List.

- Iterator will have access to Node

#### To Do List

- a way to create fresh Iterator to the start of List
- a way to represent an Iterator to the end of List
- Overload !=, ++ (unary), * (unary)

```cpp
class List {
	struct Node {
    ...;
  };
  Node *thelist = nullptr;
  public:
  class Iterator {
    Node * curr;
    public:
    explicit Iterator(node *n) : Curr{n} {}
    // *p
		int &operator*() {
			return curr->data;
		}
		// ++p
		Iterator * operator++() {
		  curr = curr->next;
		  return *this; // (unary prefix)
		}
		// Bonus: p++
		Iterator * operator (int) {
		  curr = curr->next;
		  return *this;
		}
		// !=
		bool operator!=(const Iterator &other) {
		  return curr != other.curr;
		}
  };
  
  Iterator begin() {
    return Iterator{theList};
  }
  
  Iterator end() {
    return Iterator{nullptr};
  }
  // Prev list methods
  void reset();
  int &getNextVal();
};
```

#### Client Code

```cpp
int main(void) {
	List l;
  l.addToFront(3);
  // (2);
  // (1);
  for (List::Iterator it = l.begin(); it != l.end(); ++it) {
    cout << *it << endl; // prints 1,2,3
    *it += l; // changes list to 2,3,4
  } // Alt Below
}
```

```cpp
auto x = y; // define x to be the same type as y
```

C++ has built-in support/syntax for the Iterator Design Pattern.

```cpp
for (auto i : l) {
	cout << i < endl;
} // i is int (by value)

for (auto &i : l) {
  i += l;
} // i is int &
// ref to data fields
```



### Range-Based For Loops

We can use a range-based for loop for a class, `MyClass`, if:

- `MyClass` has methods `begin`/`end`, which return objects of a class, say `Iter`.
- `Iter` must overload !=, * (unary), ++ (unary prefix)

To force clients to use begin/end, make `Iter` constructor private.

- If we make it private, `List::begin`/`List::end` will lost access (private really implies no access).
- The `Iter` class can declare `List` to be a `friend`.

```cpp
class List {
  ...;
  public:
  class Iter {
    Node * curr;
    explicit Iter(Node * p) ...;
    friend class List;
    ...;
  };
};
```

Friendship breaks encapsulation.

Advice: have as few friends as possible.