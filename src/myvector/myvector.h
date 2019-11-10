#ifndef MYmyvector
#define MYmyvector

template <typename T>
class myvector {
public:
	// fixed size init
	myvector(int maxsize);

	// move init
	myvector(myvector &&x);

	// copy init
	myvector(const myvector &x);

	~myvector();

	// move =
	myvector& operator=(myvector &&x);

	// copy =
	myvector& operator=(const myvector& x);

	// move swap
	void swap(T &a, T &b);

	T* begin();
	T* end();

	// move  
	void push_back(T&& value);

	// copy
	void push_back(const T &value);

	T& pop_back();
	int size();

private:
	T* data;
	int len = 0;
	int capacity;
};

#endif