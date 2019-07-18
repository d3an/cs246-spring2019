# Lecture 12

## Big 5 (Continued)

### Destructors

```cpp
Node *np = new Node{1, new Node{2, new Node{3, nullptr}}};
delete np; // calls destructor on Node (1); Node (2) & (3) leak
```

- every class comes with a destructor
- destructor calls destructors on fields that are objects

```cpp
Node::~Node() {
  delete next; // deleting a nullptr is safe
}
```



### Copy Assignment Operator

```cpp
Student billy{80,50,70};
Student bobby{billy}; // copy constructor
Student jane{...}
jane = billy; // copy assignment operator
jane.operator=(billy); // operator= is a method
```

Sometimes the one we get for free does not do the "correct" thing.

```cpp
Node n1{...}, n2{...}, n3{...};
n2 = n1; // n2.operator=(n1);
n3 = n2 = n1; // n3.operator=(n2.operator=(n1))
```

```cpp
Node &Node::operator=(const Node &other) {
  if (this == &other) return *this; // (2)
  data = other.data;
  delete next; // (1)
  next = other.next ? new Node{*other.next} : nullptr;
  return *this;
}
```

(1) `next` might already be pointing to heap memroy

```cpp
n1 = n1; // n1.operator = (n1);
```

- `next` and `other.next` are the same
- accessing a dangling pointer

(2) Self-Assignment Check

- If `new` fails to allocate memory, `next` is not assigned.
- Makes `next` a dangling pointer
- Better to delay deleting next until we know that new will not fail

#### Perfect Implementation

```cpp
Node &Node::operator=(const Node &other) {
  if (this == &other) return *this;
  Node *temp = next;
  
  // If this line fails, no lines after this will be run
  next = other.next ? new Node{*other.next} : nullptr;
  
  delete temp; // delaying the deleting to see if the above line fails
  data = other.data;
  return *this
}
```

#### Alternative Method - Copy & Swap Idiom

```cpp
// node.h
struct Node {
  void swap(Node &other);
  Node &operator=(const Node &);
};
```

```cpp
// node.cc
#include <utility>

void Node::swap(Node &other) {
  std::swap(data, other.data);
  std::swap(next, other.next);
}

Node &Node::operator=(const Node &other) {
  Node tmp{other}; // deep copy. Memory allocated on the stack
  swap(tmp);
  return *this;
}
```

#### Complicated Example

```cpp
// pass-by-value
Node plusOne(Node n) {
  for (Node *p {&n}; p ; p = p->next) {
    ++p->data;
  }
  // return by value
  return n;
}

int main() {
  Node n {1, new Node{2, nullptr}};
	Node n2 {plusOne(n)}; // 6 calls to copy constructor
  cout << n << endl << n2 << endl;
}
```

- 2 calls to basic constructor
- 2 calls to copy constructor (to copy arguments)
- 2 calls to copy constructor (to return)
- Node n2{returned value}
- 2 calls to copy constructor (construct n2 as copy of returned value)