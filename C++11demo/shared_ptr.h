#pragma once
#include <memory>
#include <iostream>

using namespace std;

class A {
public:
	A() :st("woshi") {
		cout << " 构造" << endl;
	}
	~A() {
		cout << " 析造" << endl;
	}

	void print() {
		if (&st) {
			cout << " print" << st << endl;
		}
		else {
			cout << " print"<< endl;
		}
	}

private:
	string st;
};

void func(std::shared_ptr<A> prt) {
	cout << "计数 2：" << prt.use_count() << endl;
}

void reference(int& v) {
	std::cout << "左值" << std::endl;
}
void reference(int&& v) {
	std::cout << "右值" << std::endl;
}
template <typename T>
void pass(T&& v) {
	std::cout << "普通传参:";
	reference(v); // 始终调用 reference(int&)

	std::cout << "       std::move 传参: ";
	reference(std::move(v));

	std::cout << "    std::forward 传参: ";
	reference(std::forward<T>(v));

	std::cout << "static_cast<T&&> 传参: ";
	reference(static_cast<T&&>(v));
}

static shared_ptr<A> prts;

template<typename Data>
class AT {
public:
	typedef std::shared_ptr<AT> APtr;
	Data getData();
};


class B : public AT<int> {
public:
	typedef std::shared_ptr<B> BPtr;
};



void testSharedPtr() {
	//shared_ptr<A> prt = make_shared<A>();
	//prts = prt;
	//cout << "计数 1：" << prt.use_count() << endl;
	//prt->print();
	//func(prt);
	////func(move(prt));
	//cout << "计数 3：" << prt.use_count() << endl;
	//prt->print();

	//std::cout << "传递右值:" << std::endl;
	//pass(1); // 1是右值, 但输出是左值

	//std::cout << "传递左值:" << std::endl;
	//int l = 1;
	//pass(l); // l 是左值, 输出左值


	//B::BPtr b = std::make_shared<B>();
	//std::cout << b << std::endl;

	////AT<int>::APtr a = std::dynamic_pointer_cast<B::BPtr>(b);
	//AT<int>::APtr a = std::dynamic_pointer_cast<B::BPtr>(b);
	//std::cout << a << std::endl;
}