//author : Manupa Karunaratne
//date : 2016.10.04

#include "print.h"
#include <iostream>
#include <string>

using namespace std;

int print_entry(OneEvent* event, std::map<uint32,std::map<uint32,const char *> >* nameMap){
	uint64 dt = (event->t);
	dt = dt << 8;
	cout << "dt=" << dt << " cycles,\t";
	cout << "duration=" << "N/A" << ",\t";
	cout << "cpu=" << event->cpu << ",\t";

	const char* tempStr;

	if(nameMap->find(event->type) != nameMap->end()){
		if(nameMap[event->type].find(event->number) != nameMap[event->type].end()){
			tempStr = (*nameMap)[event->type][event->number];
			cout << "typeName=" << tempStr << ",\t";
		}
		else{
			cout << "type=0x" << hex << event->type << dec << ",\t";
			cout << "number=0x" << hex <<  event->number << dec << ",\t";
		}
	}
	else{
		cout << "type=0x" << hex << event->type << dec << ",\t";
		cout << "number=0x" << hex <<  event->number << dec << ",\t";
	}

	cout << "rpcid=" << "N/A" << ",\t";
	cout << "arg0=0x" << hex << event->arg0 << dec << ",\t";
	cout << "return_t=0x" << hex << event->return_t << dec << ",\t";
	cout << "retval=0x" << hex << event->retval << dec;

	if(event->name != NULL){
		cout << ",\t" << "def:name=" << event->name << endl;
	}else{
		cout << endl;
	}
}