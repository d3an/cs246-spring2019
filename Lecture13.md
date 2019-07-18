# Lecture 13

## Move Operations, Operator Overloading, Arrays of Objects

### Move Operations

An rvalue reference is a reference to a temporary (an rvalue).

If a move constructor is available, it is called whenever we are constructing an object from an rvalue. If we implement any of the Big 5 (copy constructor, copy operators=, destructor, move operator=) you lose move constructor.

```c++
Node n{1, new Node{2, nullptr}};
Node n1{PlusOne(n)};
n = PlusOne(n1); // PlusOne(n1) is an rvalue

Node &Node::operator=(Node && other) {
  swap(other); // Node::swap(Node &)
  return *this;
}
```

### Rule of 5

If you need to write a custom copy constructor or copy operator=, or destructor, or move constructor, or move operator= then you usually need to write all of them.

### Copy/Move Elision

Under certain conditions, the compiler is allowed (not required) to avoid some copy/move constructor calls (even if these have side effects).

```cpp
Vec makeVec() {return Vec{_,_};}
Vec v = makeVec(); // makeVec() is temp
```

- This would cause move/copy constructor to be called
- The compiler may directly construct the Vec in the space for var v.

```cpp
Void foo(Vec v) {...}
// foo(5);
foo(makeVec());
```

- f no_elide_constructors

### Operator Overloading: Methods or standalone functions

- operator= is/must be a method

- ```cpp
  n1 = n2; // n1.operator=(n2)
  
  Vec v1{1,2};
  Vec v2{3,4};
  Vec v = v1 + v2; // v1.operator+(v2)
  v = v1 * 5; // v1.operator*(5)
  v = 5 * v1; // 5 * operator*(v)
  ```

  ```cpp
  Vec Vec::operator+(const Vec &other) {
  	return Vec{x + other.x}, y + other.y}; // implicitly, x == this->x
  }
  
  Vec Vec::operator*(const int k) {
    return Vec{x*k, y*k};
  }
  
  Vec operator*(const int, const Vec &);
  
  ostream &Vec::operator<<(ostream &out) {
    out << x << "..." << y; // v.operator<<(cout);
    return out;
  }
  
  // Usage
  Vec v...;
  v << cout;
  v2 << (v1 << cout)
  v.operator<<(cout);
  ```

```cpp
struct Vec{
	...;
	Vec(int, int);
};

Vec v; // bad
Vec arr[3]; // bad
Vec *p = new Vec[3]; // bad
```

No default constructor. Allocating an array of objects requires default constructing the elements.