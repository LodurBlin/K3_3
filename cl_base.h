#ifndef CL_BASE_H
#define CL_BASE_H
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define PROCESS_D(process_f)(TYPE_PROCESS)(&process_f)
#include <vector>
#include <string>
using namespace std;

class cl_base {
public:
	typedef void (cl_base::* TYPE_SIGNAL) (string&);
	typedef void (cl_base::* TYPE_PROCESS) (string);
private:
	string ob_name;
	int ready = 0;
	cl_base* p_predok = NULL;
	vector <cl_base*> spinogrizi;
	struct connection {
		TYPE_SIGNAL signal;
		cl_base* obj;
		TYPE_PROCESS process;
	};
	vector <connection> cons;
protected:
	int classNum;
public:
	cl_base(cl_base* p_object, string name = "");
	void set_name(string name);
	string get_name();
	void setReady(int ready);
	int getReady();
	void print_hierarchy(int level = 1);
	void printReadyTree(int level = 1);
	void setParent(cl_base* p_parent);
	void printHierarchy();
	cl_base* kto_otez();
	~cl_base();
	cl_base* search(string name);
	cl_base* findIP(string name);
	void setConnection(TYPE_SIGNAL m_signal, cl_base* obj, TYPE_PROCESS m_process);
	void delConnection(TYPE_SIGNAL m_signal, cl_base* obj, TYPE_PROCESS m_process);
	void emitSignal(TYPE_SIGNAL m_signal, string& text);
	void makeAllReady(int ready);
	string getAbs(string coord = "");
	int getClassNum();
};
#endif
