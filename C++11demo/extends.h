#pragma once
#include <memory>
#include <iostream>

using namespace std;
class Parent
{
public:
	Parent();
	~Parent();

private:

};

Parent::Parent()
{
	cout << "parent construnct" << endl;
}

Parent::~Parent()
{
	cout << "parent dis construnct" << endl;
}


class Child : public Parent
{
public:
	Child();
	~Child();

private:

};

Child::Child()
{
	cout << "child construnct" << endl;
}

Child::~Child()
{
	cout << "child dis construnct" << endl;
}

class TestC {
public:
	TestC(int value) {
		this->value = value;
	}
	using TestCPtr = std::shared_ptr<TestC>;
	bool operator > (TestCPtr messagePtr) const {
		return (this->value > messagePtr->value);
	}

	/*bool operator < (TestCPtr messagePtr) const {
		return (this->value < messagePtr->value);
	}

	bool operator==(TestCPtr messagePtr) const {
		return (this->value == messagePtr->value);
	}*/
	bool operator()(TestCPtr messagePtr, TestCPtr messagePtrR) const {
		return (messagePtr->value < messagePtrR->value);
	}
public:
	int value;
};

template<class T>
class ValComp {
public:
	bool operator()(const T& t1, const T& t2) const {
		return (t1 < t2);
	}

};

void testSharePtr(TestC::TestCPtr& testPtr) {
	cout << "count : " << testPtr.use_count() << endl;
}

void testExtends() {
	//shared_ptr<Child> c = make_shared<Child>();
	shared_ptr<TestC> c = make_shared<TestC>(3);
	testSharePtr(c);


	
	std::vector<TestC::TestCPtr> ts;
	ts.push_back(std::make_shared<TestC>(3));
	ts.push_back(std::make_shared<TestC>(6));
	ts.push_back(std::make_shared<TestC>(1));
	ts.push_back(std::make_shared<TestC>(5));
	std::sort(ts.begin(), ts.end(), [](TestC::TestCPtr messagePtr, TestC::TestCPtr messagePtrR) {
		return (messagePtr->value < messagePtrR->value);
		});
	for (auto &p: ts)
	{
		std::cout<< p->value << endl;
	}
}