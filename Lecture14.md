# Lecture 14

## Arrays/const methods/invariants/encapsulation

```cpp
struct Vec {
	int x, y;
  Vec(int, int);
};
Vec arr[3];							// Won't compile as default
Vec *arr = new Vec[3]; 	// constructors are gone
```

### Options

1. Implement a default (0 parameter constructor)

2. Stack arrays: use C's array initializing syntax

   ```cpp
   Vec arr[3] = {Vec{1,2}, Vec{3,4}, Vec{5,6}};
   ```

3. Instead of array of objects, create array of pointers to object

   ```cpp
   Vec *arr[3];
   Vec **arr = new Vec*[3];
   ```

   ```cpp
   arr[i] = new Vec{1,2};
   for (...) {
     delete arr[i];
   }
   delete []arr;
   ```

   

### Const Methods

```cpp
struct Student {
	int assns, mt, final;
	float grade() {
		return 0.4 * assns + 0.2 * mt + 0.4 * final;
	}
};
const Student billy{80,50,70};
cout << billy.grade(); // won't compile
```

Problem: grade does not promise to not change fields.

- We can promise this by declaring the method **const**

- Const objects can only call methods that are constant.

- Fix:

- ```cpp
  struct Student {
  	int assns, mt, final;
  	float grade() const {
  		return 0.4 * assns + 0.2 * mt + 0.4 * final;
  	}
  };
  ```

### Invariants

```cpp
struct Node {
  int data;
  Node *next;
  Node(int, int);
  ~Node() { delete next; }
}

Node n1{1, new Node{2, nullptr}};
Node n2{3, nullptr};
Node n3{4, &n1};
```

When n1, n2, n3 are out of scope, the destructor will run automatically. Next of n3 is a stack address; cannot call delete. `~Node` assumed next is either `nullptr` or points to heap

**Invariant:** some assumption/statement that must not be violated for program to function correctly

**Stack class:** Last In First Out

We need to hide information/implementation to protect invariants.

## Encapsulation

- treat objects as capsules (black box)
- interact through provided method (interface)

### Public/Private Labels

```cpp
struct Vec {
	Vec(int, int); // default visibility is public
  private:
  int x,y; // not visible from outside class
  public:
  Vec operator+(const Vec &);
};

Vec Vec::operator+(const Vec &o) {
  return Vec{x + o.x, y + o.y};
}

int main(void) {
  Vec v{1,2}; // default visibility was public
  Vec v1 = (v + v); // rvalue // operator+ is public
  cout << v1.x v1.y; // Bad since x,y are private
}
```

Advice: at a minimum, keep all fields private. Make select methods public.

```cpp
struct ... {}; // default visibility is public (inherent from C)
class ... {}; // default visibility is private
```

```cpp
class Vec {
	int x,y; // private by default
	public:
	Vec(int, int);
	Vec operator+(const Vec &);
};
```

### Node Invariant

We will wrap Nodes within a List class

```cpp
// list.h
class List {
  struct Node; // declare Node as private/nested class
  Node *thelist = nullptr;
  public:
  void addToFront(int n);
  int ith(int i);
  ~List();
};
```

```cpp
// list.cc
struct List::Node {
  int data;
  Node *next;
  Node(int, Node*);
  ~Node() {
    delete next;
  }
};

List::~List() {
  delete theList;
}

void List::addToFront(int n) {
  theList = new Node{n, theList};
}

int List::ith(int i) { // assume i is in range
  Node *cur = thelist;
  for (int j = 0; j < i && cur; ++j, cur = cur->next);
  return cur->data;
} // Traversal is O(n^2)
```

