//author : Manupa Karunaratne
//date : 2016.10.04

#include "print.h"
#include <iostream>
#include <string>

using namespace std;

int print_entry(OneEvent* event, std::map<uint32,std::map<uint32,const char *> >* nameMap){
	cout << "dt=" << (event->t << 8) << " cycles,\t";
	cout << "duration=" << "N/A" << ",\t";
	cout << "cpu=" << event->cpu << ",\t";

	const char* tempStr;

	if(nameMap->find(event->type) != nameMap->end()){
		if(nameMap[event->type].find(event->number) != nameMap[event->type].end()){
			tempStr = (*nameMap)[event->type][event->number];
			cout << "typeName=" << tempStr << ",\t";
		}
		else{
			cout << "type=" << event->type << ",\t";
			cout << "number=" << event->number << ",\t";
		}
	}
	else{
		cout << "type=" << event->type << ",\t";
		cout << "number=" << event->number << ",\t";
	}

	cout << "rpcid=" << "N/A" << ",\t";
	cout << "arg0=" << event->arg0 << ",\t";
	cout << "return_t=" << event->return_t << ",\t";
	cout << "retval=" << event->retval;

	if(event->name != NULL){
		cout << ",\t" << "def:name=" << event->name << endl;
	}else{
		cout << endl;
	}
}