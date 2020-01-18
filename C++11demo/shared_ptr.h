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
	//cout << "���� 1��" << prt.use_count() << endl;
	//prt->print();
	//func(prt);
	////func(move(prt));
	//cout << "���� 3��" << prt.use_count() << endl;
	//prt->print();

	//std::cout << "������ֵ:" << std::endl;
	//pass(1); // 1����ֵ, ���������ֵ

	//std::cout << "������ֵ:" << std::endl;
	//int l = 1;
	//pass(l); // l ����ֵ, �����ֵ


	//B::BPtr b = std::make_shared<B>();
	//std::cout << b << std::endl;

	////AT<int>::APtr a = std::dynamic_pointer_cast<B::BPtr>(b);
	//AT<int>::APtr a = std::dynamic_pointer_cast<B::BPtr>(b);
	//std::cout << a << std::endl;
}