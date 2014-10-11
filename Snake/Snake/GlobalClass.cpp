#include "StdAfx.h"
#include "GlobalClass.h"
#include <iostream>


void GlobalClass::doAnything() {
	std::cout << "GlobalClass is doing anything..." << std::endl; 
}

GlobalClass::GlobalClass(void)
{
}

GlobalClass::~GlobalClass(void)
{
}
