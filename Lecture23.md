# Lecture 23

### Last time: smart pointers

`unique_ptr<T>`

- destructor deletes heap object

`shared_ptr<T>`

- reference counting
- copying increments refcount
- destructors decrement refcount
- delete if refcount is 0

### Levels of Exception Safety

**Basic Guarantee:** If an exception occurs, the program is in a valid (memory intact), but unspecified state

**Strong Guarantee:** If an exception occurs while executing `f()`, it is as if `f()` was never called.

**No-throw Guarantee:** Function `f()` does not throw an exception and always achieves its goal.

```cpp
class A{...};
class B{...};
class C{
  A a;
  B b;
  
  void foo() {
    a.method1(); // strong guarantee
    b.method2(); // strong guarantee
  }
};
```

Scenario: What if method2 fails?

- "undo" method1??
- typically impossible for non-local side-effects

Let's assume method1/method2 only have local side effects

- undoing method1 would mean undoing changes to object "a"

Idea: Work on copies of "a" and "b". If successful, swap with originals

```cpp
void C::foo() {
	A tempA{a};
	B tempB{b};
	
	tempA.method1();
	tempB.method2();
	
	a = tempA;
	b = tempB; // if B::operator= throws, we lose our strong guarantees
}
```

Pointer assignment is no throw!!

```cpp
struct CImpl{A a; B b;};
class C {
  unique_ptr<CImpl> pImpl;
  
  // Strong guarantee
  void foo() {
    unique_ptr<CImpl> temp = make_unique<CImpl>(*pImpl);
    // Also works: unique_ptr<CImpl> temp{new Cimpl{*pImpl}};
    temp->a.method1();
    temp->b.method2();
    swap(pImpl, temp);
  }
};
```



### Exception Safety in the STL

`std::vector`

- uses RAII
- heap allocates array, destructor deallocates array

```cpp
void foo() {
	vector<MyClass> v;
	...
}
// When v goes out of scope, elements are automatically destroyed
// vector destructor frees the array
```

```cpp
void g() {
	vector<MyClass *> v;
  for (auto &m : v) delete m;
}
```

```cpp
void h() {
	vector<unique_ptr<MyClass>> v;
}
```

`vector::emplace_back` provides a strong guarantee

- Easy case:
  - size < cap
  - place object at end
  - increment size
- Harder case:
  - Less-efficient:
    - size == cap
    - create new larger array
    - copy from old to new (if exception, delete new array)
    - delete old (no-throw)
  - More-efficient:
    - create new larger array
    - move from old to new (if an exception occurs, you lose strong guarantee)
    - delete old

Note: only use move operations if they are labelled `noexcept`



## Casting

#### Casting in C:

```c
Node n;
int *p = (int *) &n;
*p = 10;
```



### 4 Casts in C++:

### `static_cast`

```cpp
void foo(int);
void foo(double);
...
double a = ...
foo(a); // foo(double)
foo(static_cast<int>(a));
```

```cpp
Book *bp = new Text{...};
Text *tp = static_cast<Text *>(bp);
// unchecked cast
// Behaviour undefined if bp is not pointing to a Text
```



### `reinterpret_cast`

- to treat any type as any other type

```cpp
Student s;
Turtle *tp = reinterpret_cast<Turtle *>(&s);
tp->draw();
```



### `const_cast`

- a cast to remove "const" from a variable 

```cpp
void foo(int * q) {...}
...
const int *q = ...;
foo(q); // won't compile
foo(const_cast<int *>(q)); // will compile
```



### `dynamic_cast`



### Fourth cast in next lecture...