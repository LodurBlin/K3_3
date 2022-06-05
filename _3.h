#ifndef _3_H
#define _3_H
#include "cl_base.h"
#include <iostream>
class _3 : public cl_base {
public:
	_3(cl_base* p_object, string ob_name = "") :cl_base(p_object, ob_name)
	{
		this->classNum = 3;
	}
	void signal(string& text) {
		std::cout << "\nSignal from " << getAbs();
		text += " (class: 3)";
	}
	void process(string text) {
		std::cout << "\nSignal to " << getAbs() << " Text: " << text;
	}
};
#endif
