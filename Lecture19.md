# Lecture 19

## Exceptions (cont'd), Design Patterns

### Last Time: `callchain.cc`

Exception recovery can be done in stages

```cpp
try {...}
catch (someExn e) { // catches someExn or a subclass
	// do part of recovery
  throw otherExn{...};
}
```

1. Throw some other exception
2. `throw e; // throw the caught exception`
3. `throw; // throws original exception`

All C++ library exceptions inherit from `std::exception`. C++ does not require exceptions to inherit from `std::exception`. In C++ you can throw anything.

**Good Practice:** Throw objects of existing exceptions or create your own exception classes

```cpp
class BadInput {};

int n;
if (!(cin >> n)) throw BadInput {};

try {
	foo();
} catch(BadInput &) {
	n = 0;
}
```

Advice: catch by reference:

- out_of_range
- bad_alloc
- length_error

### Observer Pattern

#### Publish/subscribe model

- Publish: Subject aggregates data
- Subscribe: Observer wants to be notified of new data

### Decorator Pattern

![DECOR_1](/Users/jamesbury/Desktop/2B/2B Study/CS246/Pictures/DECOR_1.jpg)

- Scroll IS-A Window
- Scroll HAS-A Window

```cpp
Window *w = new BasicWindow();
w = new Scroll{w};
w = new Menu{Scroll};
w->display();
```

