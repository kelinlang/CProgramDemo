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

void testSharedPtr() {
	shared_ptr<A> prt = make_shared<A>();
	cout << "计数 1：" << prt.use_count() << endl;
	prt->print();
	func(move(prt));
	cout << "计数 3：" << prt.use_count() << endl;
	prt->print();
}