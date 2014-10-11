// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

DWORD WINAPI test(LPVOID a) {
	return 0;
}

class Test {
public:
	Test();
	~Test();
	static DWORD WINAPI thread(LPVOID a);
	static DWORD WINAPI thread2(LPVOID a);
};

DWORD WINAPI Test::thread(LPVOID a) {
	while(true) { cout << "1"; }
	return 0;
}

DWORD WINAPI Test::thread2(LPVOID a) {
	while(true) { cout << "2"; }
	return 0;
}

Test::Test() {
	CreateThread(NULL, NULL, &Test::thread, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &Test::thread2, NULL, NULL, NULL);
}

Test::~Test() {

}

int _tmain(int argc, _TCHAR* argv[])
{
	Test test;
	getch();
	return 0;
}