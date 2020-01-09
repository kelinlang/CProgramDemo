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

void reference(int& v) {
	std::cout << "��ֵ" << std::endl;
}
void reference(int&& v) {
	std::cout << "��ֵ" << std::endl;
}
template <typename T>
void pass(T&& v) {
	std::cout << "��ͨ����:";
	reference(v); // ʼ�յ��� reference(int&)

	std::cout << "       std::move ����: ";
	reference(std::move(v));

	std::cout << "    std::forward ����: ";
	reference(std::forward<T>(v));

	std::cout << "static_cast<T&&> ����: ";
	reference(static_cast<T&&>(v));
}

static shared_ptr<A> prts;

void testSharedPtr() {
	shared_ptr<A> prt = make_shared<A>();
	prts = prt;
	cout << "���� 1��" << prt.use_count() << endl;
	prt->print();
	func(prt);
	//func(move(prt));
	cout << "���� 3��" << prt.use_count() << endl;
	prt->print();


	//std::cout << "������ֵ:" << std::endl;
	//pass(1); // 1����ֵ, ���������ֵ

	//std::cout << "������ֵ:" << std::endl;
	//int l = 1;
	//pass(l); // l ����ֵ, �����ֵ
}