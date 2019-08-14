// A simple implementation for shared_ptr that does not use RAII in implementation

template <typename T> class shared_ptr {
	T * ptr;
	size_t * counter;

public:
	shared_ptr() : ptr{nullptr}, counter{new size_t{0}} {}
	shared_ptr(T * ptr) : ptr{ptr}, counter{new size_t{1}} {}
	shared_ptr(const shared_ptr<T> & other) : ptr{other.ptr}, counter{other.counter} {
		++(*counter);
	}

	~shared_ptr() {
		if (!counter) {
			--(*counter);
		}

		if (*counter == 0) {
			delete ptr;
			delete counter;
		} else {

		}
	}

};

