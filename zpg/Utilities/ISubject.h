#pragma once
#include <iostream>
#include <list>
#include <string>
#include "IObserver.h"
class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};
