#pragma once
#include <memory>
#include <iostream>

using namespace std;

class A {
public:
	A() :st("woshi") {
		cout << " ����" << endl;
	}
	~A() {
		cout << " ����" << endl;
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
	cout << "���� 2��" << prt.use_count() << endl;
}

void testSharedPtr() {
	shared_ptr<A> prt = make_shared<A>();
	cout << "���� 1��" << prt.use_count() << endl;
	prt->print();
	func(move(prt));
	cout << "���� 3��" << prt.use_count() << endl;
	prt->print();
}