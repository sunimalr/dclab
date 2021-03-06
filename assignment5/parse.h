//author : Manupa Karunaratne
//date : 2016.10.04

#ifndef __PARSE_H__
#define __PARSE_H__

#include "common.h"
#include "basetypes.h"
#include <map>
#include <vector>
#include <cstddef>

uint64 updateN(OneEvent* event, uint64 word);
int updateName(OneEvent* event, 
	           std::vector<uint64> word, 
	           std::map<uint32,std::map<uint32,const char *> >* = NULL);
uint64 updateArgRet(OneEvent* event, uint64 word);

#endif	// __PARSE_H__
