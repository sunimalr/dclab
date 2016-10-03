#include "updateN.h"
#include <assert.h>


uint64 updateN(OneEvent* event, uint64 word){
	uint64 N;

	N = (word >> 32) & 0x0000000000000fff;

	if(N >= 0x200){
		event->type = N & 0xf00;
		event->number = N & 0x0ff;
	}
	else if(N >= 0x010){
		//for variable length we are using 0x100 as bitmasked type
		event->type = 0x100;
		event->number = N & 0x00f;
	}
	else if(N >= 003){
		assert(false);
	}
	else{
		event->type = N;
		event->number = 0; //no sub-types
	}

	return N;
}

int updateName(OneEvent* event, 
	           uint64 word, 
	           std::map<uint32,std::map<uint32,const char *> >* nameMap){

	if(event->type == 0x100){
		uint64 hashNumber = word & 0x000000000000ffff;
		switch(event->number){
			case 0x2 :
			case 0x4 :
			case 0x5 :
			case 0x8 :
			case 0xC :
			case 0x3 :
			case 0x1 :
				//(*nameMap)[event->number][hashNumber]

				break;
			default :
				assert(false);
		}

		return 0;
	}
	event->name = NULL;
	return -1;
}

