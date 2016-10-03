#include "print.h"
#include <iostream>
#include <string>

using namespace std;

int print_entry(OneEvent* event, std::map<uint32,std::map<uint32,const char *> >* nameMap){
	cout << "t=" << event->t << ",";
	cout << "duration=" << "N/A" << ",";
	cout << "cpu=" << event->cpu << ",";

	const char* tempStr;

	if(nameMap->find(event->type) != nameMap->end()){
		if(nameMap[event->type].find(event->number) != nameMap[event->type].end()){
			tempStr = (*nameMap)[event->type][event->number];
			cout << "typeName=" << tempStr << ",";
		}
		else{
			cout << "type=" << event->type << ",";
			cout << "number=" << event->number << ",";
		}
	}
	else{
		cout << "type=" << event->type << ",";
		cout << "number=" << event->number << ",";
	}

	cout << "rpcid=" << "N/A" << ",";
	cout << "arg0=" << event->arg0 << ",";
	cout << "return_t=" << event->return_t << ",";
	cout << "retval=" << event->retval << endl;
}