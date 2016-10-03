//author : Manupa Karunaratne
//date : 2016.10.04

#ifndef __PRINT_H__
#define __PRINT_H__

#include "common.h"
#include <map>

int print_entry(OneEvent* event, std::map<uint32,std::map<uint32,const char *> >* nameMap);

#endif	// __PRINT_H__