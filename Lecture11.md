# Lecture 11

## Object Initialization, Copying, Destroying

Last time: initializing fields that are const/refs.

In-class initialization, not what we need:

```c++
struct Student {
	const int id = 20733115;
	int assns, mt, final;
};
```

Can't assign in constructor body.

### Steps for Object Construction:

1. Space is allocated
2. Field initialization: call default constructors for fields that are objects
3. Constructor body runs

Let's "hijack" step 2 using Member Initialization List (MIL)

- syntax available only in constructors
- can be used to initialize all/some fields

```c++
Student::Student(int id, int assns, int mt, int final) : 
	id{id}, assns{assns}, mt{mt}, final{final} {}
// field is first parameter, i.e. field = final, but not {final}
// second parameter points to declaration, i.e. {final} points to int final
```

- MIL always initializes fields in declaration order
- In some cases, using an MIL to initialize a field is more efficient than assigning it in the constructor body

```c++
struct Bla {
	Student s;
	Vec v;
};
```

```c++
struct Vec {
	int x = 0;
	int y = 0;
	Vec(int x, int y);
};
Vec::Vec(int x, int y) : x{x}, y{y} {}
```

```c++
Vec v{3,4};
```

MIL has priority over in-class initialization.

### Copy Constructors

```c++
Student billy{80,50,70};
Student bobby{billy};
// Student bobby = billy;
```

Construct an object as a copy of an existing object

- We get one for free
- Copies fields of existing object into the new object

Every class comes with:

- default (0 param) constructor
- Big 5
  - copy constructor
  - destructor
  - copy assignment operator
  - move constructor
  - move assignment operator

A copy constructor takes a reference of the existing object.

```cpp
Student::Student(const Student &other)
	: assns{other.assns}, mt{other.mt}, final{other.final} {}
```

The free copy constructor might not always do the "correct" thing.

```cpp
struct Node {
	int data;
	Node *next;
	Node(int, Node *);
	Node(const Node &);
};
Node::Node(int data, Node *next) : data{data}, next{next} {}
Node::Node(const Node &other) : data{other.data}, next{other.next} {}
Node *np = new Node{1, new Node{2, new Node{3, nullptr}}};
// np is on the stack, {1, 2, 3} nodes are on the heap
Node n1{*np}; // Calls copy constructor
							// Node n1 = *np;
Node *n2 = new Node{*np}; // copy constructor
struct llNode *np = malloc(sizeof(struct llNode));
```

Refer to https://github.com/RRethy/NOTES-CS246/blob/master/oct_11.md for diagrams.



### Deep Copy Constructor

```cpp
Node::Node(const Node &other) {
  data = other.data;
  // next = new Node{*other.next};
  if (other.next) next = new Node {*other.next};
  else next = nullptr; // Deep copy
}
```

```cpp
Node::Node(const Node &other) :
	data{other.data},
	next{other.next ? new Node{*other.next} 
      						: nullptr} {}
// A ? expr1 : (B ? expr2 : expr3)
```

A copy constructor is called

1. constructing object as a copy of an existing object
2. passing an object by value
3. returning an object by value

It is (2) which is the reason why a param to a copy constructor is a reference.



### Constructors with one parameter

```cpp
{explicit} Node::Node(int data) : data{data}, next{nullptr} {} // Explicit key word makes line 5 & 6 invalid
Node n{4};
void foo(Node);
foo(n);
Node = 4; // Valid
foo(10); // Valid
```

Single parameter constructors create implicit or automatic conversions.