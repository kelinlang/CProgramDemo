#pragma once
#include <iostream>
using namespace std;

void print() {
	cout << "empty" << endl;
}

template <typename T, typename ...Args> void print(T head, Args... args) {
	cout << "parameter " << head << endl;
	print(args...);
}


template <class T, class R, typename ...Args>
class MyDelegate {
public:
	MyDelegate(T* t, R (T::*f)(Args...)):m_t(t),m_f(f){}

	R operator ()(Args&&... args) {
		return (m_t->*m_f)(forward<Args>(args) ...);
	}

private:
	T* m_t;
	R (T::*m_f)(Args...);
};

template <class T, class R, typename ...Args>
MyDelegate<T, R, Args...> createDelegate(T* t, R(T::* f)(Args...)) {
	return MyDelegate<T, R, Args...>(t, f);
}

struct TestTemplate
{
	void fun(int i) {
		cout << i << endl;
	}

	void fun1(int i,double j) {
		cout << i +j<< endl;
	}
};

//int main() {
//	TestTemplate a;
//	auto d = createDelegate(&a, &TestTemplate::fun);
//}