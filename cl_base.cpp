#include <iostream>
#include <vector>
#include <string>
#include "cl_base.h"
using namespace std;
cl_base::cl_base(cl_base* p_object, string s_name) {
	this->ob_name = s_name;
	p_predok = p_object;
	if (p_object) {
		p_object->spinogrizi.push_back(this);
	}
}
void cl_base::set_name(string ob_name) {
	this->ob_name = ob_name;
}
string cl_base::get_name() {
	return ob_name;
}
void cl_base::printHierarchy() {
	if (!p_predok) {
		cout << ob_name;
	}
	if (spinogrizi.size()) {
		cout << endl << ob_name;
		for (int i = 0; i < spinogrizi.size(); i++) {
			cout << spinogrizi[i]->get_name();
		}
		spinogrizi[spinogrizi.size() - 1]->printHierarchy();
	}
}
void cl_base::print_hierarchy(int level) {
	cout << ob_name;
	for (int i = 0; i < spinogrizi.size(); i++)
	{
		cout << endl;
		for (int j = 0; j < level; j++) {
			cout << " ";
		}
		spinogrizi[i]->print_hierarchy(level + 1);
	}
}
void cl_base::printReadyTree(int level) {
	cout << ob_name;
	if (ready != 0) cout << " is ready";
	else cout << " is not ready";
	for (int i = 0; i < spinogrizi.size(); i++)
	{
		cout << endl;
		for (int j = 0; j < level; j++) {
			cout << 4*' ';
		}
		spinogrizi[i]->printReadyTree(level + 1);
	}
}
void cl_base::setParent(cl_base* p_parent) {
	if (p_predok && p_parent) {
		for (int i = 0; i < p_predok->spinogrizi.size(); i++) {
			if (p_predok->spinogrizi[i] == this) {
				p_predok->spinogrizi.erase(p_predok->spinogrizi.begin() + i);
				break;
			}
		}
		p_predok = p_parent;
		p_parent->spinogrizi.push_back(this);
	}
}
cl_base* cl_base::kto_otez() {
	return p_predok;
}
cl_base:: ~cl_base() {
	for (int i = 0; i < spinogrizi.size(); i++) {
		delete spinogrizi[i];
	}
}
int cl_base::getReady() {
	return ready;
}
void cl_base::setReady(int ready) {
	if (!p_predok || p_predok->getReady() != 0) {
		if (ready == 0) {
			for (int i = 0; i < spinogrizi.size(); i++) {
				spinogrizi[i]->setReady(0);
			}
		}
		this->ready = ready;
	}
}
cl_base* cl_base::search(string ob_name) {
	if (spinogrizi.size() == 0 && this->get_name() != ob_name) {
		return nullptr;
	}
	else if (this->ob_name == ob_name) {
		return this;
	}
	else {
		for (int i = 0; i < spinogrizi.size(); i++) {
			cl_base* child = spinogrizi[i]->search(ob_name);
			if (child != nullptr) {
				return child;
			}
		}
	}
	return nullptr;
}
cl_base* cl_base::findIP(string cn) {
	cl_base* p_root = this;
	cl_base* p_obj = nullptr;
	string s_root = "", s_name = "";
	bool flag = true;
	while (p_root->kto_otez() != nullptr) {
		p_root = p_root->kto_otez();
	}
	// поиск от корневого
	if (cn[0] == '/' && cn[1] == '/') {
		for (int i = 2; i < cn.size(); i++) {
			s_name += cn[i];
		}
		return p_root->search(s_name);
	}
	//корневой
	else if (cn == "/") return p_root;
	//текущий
	else if (cn == ".") return this;
	//поиск по координате
	else {
		for (int i = 0; i < cn.size(); i++) {
			//если начался вводится корневой объект для поиска
			if (cn[i] == '/' && s_root == "") {
				continue;
			}
			// вводится корневой объект
			else if (cn[i] != '/' && flag) {
				s_root += cn[i];
			}
			// начинает вводиться искомый
			else if (cn[i] == '/') {
				flag = 0;
				s_name += cn[i];
			}
			// ввод искомого
			else {
				s_name += cn[i];
			}
		}
		for (int i = 0; i < this->spinogrizi.size(); i++) {
			if (this->spinogrizi[i]->get_name() == s_root) {
				if (s_name == "") {
					return this->spinogrizi[i];
				}
				else {
					p_obj = this->spinogrizi[i]->findIP(s_name);
					if (p_obj != nullptr) {
						return p_obj;
					}
				}
			}
		}
	}
	return nullptr;
}
void cl_base::makeAllReady(int ready) {
	this->ready = ready;
	for (int i = 0; i < spinogrizi.size(); i++) {
		spinogrizi[i]->makeAllReady(ready);
	}
}
string cl_base::getAbs(string coord) {
	if (!p_predok) {
		return "/";
	}
	return p_predok->getAbs("/") + ob_name + coord;
}
int cl_base::getClassNum() {
	return classNum;
}
void cl_base::setConnection(TYPE_SIGNAL m_signal, cl_base* obj, TYPE_PROCESS m_process)
{
	for (int i = 0; i < cons.size(); i++) {
		if (cons[i].signal == m_signal && cons[i].process == m_process) {
			return;
		}
	}
	connection c;
	c.signal = m_signal;
	c.process = m_process;
	c.obj = obj;
	cons.push_back(c);
}
void cl_base::delConnection(TYPE_SIGNAL m_signal, cl_base* obj, TYPE_PROCESS m_process)
{
	for (int i = 0; i < cons.size(); i++) {
		if (cons[i].signal == m_signal && cons[i].process == m_process) {
			cons.erase(cons.begin() + i);
			return;
		}
	}
}
void cl_base::emitSignal(TYPE_SIGNAL m_signal, string& text) {
	if (ready != 0 && !cons.empty()) {
		(this->*m_signal)(text);
		for (int i = 0; i < cons.size(); i++) {
			if (cons[i].signal == m_signal && cons[i].obj->ready != 0) {
				(cons[i].obj->*(cons[i].process))(text);
			}
		}
	}
}
