#include "updateN.h"
#include <assert>

int updateN(OneEvent* event, uint64 word){
	uint64 N;

	N = (word >> 32) & 0x0000_0000_0000_0fff;

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

	return 0;
}