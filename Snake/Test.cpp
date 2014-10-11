#include "StdAfx.h"
#include "Test.h"
#include <iostream>

void Test::testPublic() {
	Test::testInt = 20;
	std::cout << "testPublic" << std::endl;
	Test::testPrivate();
}

void Test::testPrivate() {
	std::cout << "testPrivate" << std::endl;
	std::cout << Test::testInt << std::endl;
}

Test::Test(void)
{
}

Test::~Test(void)
{
}