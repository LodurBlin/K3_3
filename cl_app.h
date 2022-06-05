#ifndef CL_APP_H
#define CL_APP_H
#include "cl_base.h"
#include <iostream>
class cl_app : public cl_base {
public:
	cl_app(cl_base* p_object);
	void derevo();
	int print();
	void signal(string& message);
	void process(string text);
	cl_base::TYPE_SIGNAL getSignal(cl_base* obj);
	cl_base::TYPE_PROCESS getProcess(cl_base* obj);
};
#endif
