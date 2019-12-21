#pragma once
#include <iostream>
using namespace std;

void print() {
	cout << "empty" << endl;
}

template <typename T, typename ...Args> void print(T head, Args... args) {
	cout << "parameter " << endl;
	print(args...);
}