#ifndef Observer_H
#define Observer_H

class Observer{

public:
	Observer () {}
	virtual ~Observer() {}
	virtual void Update() = 0;
};
#endif 