#ifndef __NODE_H
#define __NODE_H
#include "cl_base.h"
class Node : public cl_base {
public:
	Node(cl_base* p_object, string s_name = "") : cl_base(p_object, s_name) {};
};
#endif
