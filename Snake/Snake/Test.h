#pragma once

class Test
{
public:
	Test(void);
	~Test(void);
	void testPublic();
private:
	void testPrivate();
	int testInt;
	static int testStaticInt;
};