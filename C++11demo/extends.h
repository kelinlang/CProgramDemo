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


void testExtends() {
	shared_ptr<Child> c = make_shared<Child>();
}