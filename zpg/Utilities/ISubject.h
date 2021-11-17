#pragma once
#include <iostream>
#include <list>
#include <string>
#include "IObserver.h"
#include "IPositionObserver.h"
class ISubject {
public:
	virtual ~ISubject() {};
	virtual void attach(IObserver* observer) = 0;
	virtual void detach(IObserver* observer) = 0;
	virtual void attach(IPositionObserver* observer) = 0;
	virtual void detach(IPositionObserver* observer) = 0;
	virtual void notify() = 0;
};
