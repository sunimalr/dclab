#ifndef __UPDATEN_H__
#define __UPDATEN_H__

#include "common.h"
#include "basetypes.h"
#include <map>
#include <cstddef>

uint64 updateN(OneEvent* event, uint64 word);
int updateName(OneEvent* event, 
	           uint64 word, 
	           std::map<uint32,std::map<uint32,const char *> >* = NULL);

#endif	// __UPDATEN_H__