#ifndef _2_H
#define _2_H
#include "cl_base.h"
#include <iostream>
class _2 : public cl_base {
public:
	_2(cl_base* p_object, string ob_name = "") : cl_base(p_object, ob_name) {
		this->classNum = 2;
	}
	void signal(string& text) {
		std::cout << "\nSignal from " << getAbs();
		text += " (class: 2)";
	}
	void process(string text) {
		std::cout << "\nSignal to " << getAbs() << " Text: " << text;
	}
};
#endif
