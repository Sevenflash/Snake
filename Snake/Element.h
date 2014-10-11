#pragma once

class Element
{
public:
	Element(void);
	~Element(void);
	void setType(int type);
	int getType();
	void setKey(int key);
	int getKey();

	virtual void draw();
	virtual void update();

	// for snakeElement
	virtual void setAsHead() {};
	virtual bool isHead() {return true;};
private:
	int key;
protected:
	int type;
};