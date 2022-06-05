#include <iostream>
#include "cl_app.h"
#include "Node.h"
#include "_2.h"
#include "_3.h"
#include "_4.h"
#include "_5.h"
#include "_6.h"
using namespace std;
cl_app::cl_app(cl_base* p_object) : cl_base(p_object) {
	classNum = 1;
}
void cl_app::derevo() {
	string root_name, s_sub;
	int clas;
	cin >> root_name;
	set_name(root_name);
	cl_base* cur_predok = this;
	while (cin >> root_name) {
		if (root_name == "endtree") {
			break;
		}
		cin >> s_sub >> clas;
		if (root_name == "/") {
			cur_predok = this;
		}
		else {
			cur_predok = findIP(root_name);
		}
		if (cur_predok == nullptr) {
			cout << "Object tree\n";
			print_hierarchy();
			cout << "\nThe head object " << root_name << " is not found";
			exit(0);
		}
		switch (clas) {
			case 2: {
				new _2(cur_predok, s_sub);
				break;
			}
			case 3: {
				new _3(cur_predok, s_sub);
				break;
			}
			case 4: {
				new _4(cur_predok, s_sub);
				break;
			}
			case 5: {
				new _5(cur_predok, s_sub);
				break;
			}
			case 6: {
				new _6(cur_predok, s_sub);
				break;
			}
		}
	}
	string s_source, s_handler;
	cl_base* p_source, * p_handler;
	while (cin >> s_source) {
		if (s_source == "end_of_connections") break;
		cin >> s_handler;
		p_source = findIP(s_source);
		if (p_source == nullptr) {
			cout << "\nObject " << s_source << " not found";
			continue;
		}
		p_handler = findIP(s_handler);
		if (!p_handler) {
			cout << "\nHandler object " << s_handler << " not found";
			continue;
		}
		p_source->setConnection(getSignal(p_source), p_handler,
			getProcess(p_handler));
	}
}
int cl_app::print() {
	cout << "Object tree" << endl;
	print_hierarchy();
	string command, s_source, s_processor, text;
	int ready;
	cl_base* p_source, * p_processor;
	makeAllReady(1);
	while (cin >> command) {
		if (command == "END") {
			break;
		}
		if (command == "EMIT") {
			cin >> s_source;
			p_source = findIP(s_source);
				if (p_source) {
					getline(cin, text);
					p_source->emitSignal(getSignal(p_source), text);
				}
				else {
					cout << endl << "Object " << s_source << " not found";
				}
		}
		if (command == "DELETE_CONNECT") {
			cin >> s_source;
			p_source = findIP(s_source);
			if (p_source) {
				cin >> s_processor;
				p_processor = findIP(s_processor);
				if (p_processor) {
					p_source->delConnection(getSignal(p_source),
						p_processor, getProcess(p_processor));
				}
				else {
					cout << endl << "Handler object " << s_processor <<
						" not found";
				}
			}
			else {
				cout << endl << "Object " << s_source << " not found";
			}
		}
		if (command == "SET_CONNECT") {
			cin >> s_source;
			p_source = findIP(s_source);
			if (p_source) {
				cin >> s_processor;
				p_processor = findIP(s_processor);
				if (p_processor) {
					p_source->setConnection(getSignal(p_source),
						p_processor, getProcess(p_processor));
				}
				else {
					cout << endl << "Handler object " << s_processor <<
						" not found";
				}
			}
			else {
				cout << endl << "Object " << s_source << " not found";
			}
		}
		if (command == "SET_CONDITION") {
			cin >> s_source >> ready;
			p_source = findIP(s_source);
			if (p_source) {
				p_source->setReady(ready);
			}
			else {
				cout << endl << "Object " << s_source << " not found";
			}
		}
	}
	return 0;
}
void cl_app::signal(string& text) {
	std::cout << "\nSignal from " << getAbs();
	text += " (class: 1)";
}
void cl_app::process(string text) {
	std::cout << "\nSignal to " << getAbs() << " Text: " << text;
}
cl_base::TYPE_SIGNAL cl_app::getSignal(cl_base* obj) {
	int clas = obj->getClassNum();
	switch (clas) {
		case 1: return SIGNAL_D(cl_app::signal);
		case 2: return SIGNAL_D(_2::signal);
		case 3: return SIGNAL_D(_3::signal);
		case 4: return SIGNAL_D(_4::signal);
		case 5: return SIGNAL_D(_5::signal);
		case 6: return SIGNAL_D(_6::signal);
	}
	return nullptr;
}
cl_base::TYPE_PROCESS cl_app::getProcess(cl_base* obj) {
	int clas = obj->getClassNum();
	switch (clas) {
		case 1: return PROCESS_D(cl_app::process);
		case 2: return PROCESS_D(_2::process);
		case 3: return PROCESS_D(_3::process);
		case 4: return PROCESS_D(_4::process);
		case 5: return PROCESS_D(_5::process);
		case 6: return PROCESS_D(_6::process);
	}
	return nullptr;
}
