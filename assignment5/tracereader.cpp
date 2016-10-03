#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>		// gettimeofday
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "basetypes.h"

using namespace std;

struct OneEvent{
	uint64 t;		// 20-bit time T in 60-125 nsec increments
	uint32 duration;	//   -unused- this week, 0
	uint32 cpu;		// copied into each struct from the first word of the block
	uint32 type;		// syscall, etc. N with variable bits masked out
	uint32 number;	// which particular syscall, particular process id, etc. N's variable bits, or other id number
	uint32 rpcid;		//   -unused- this week, 0
	uint32 arg0;		//  0 if unused
	uint64 return_t;	//  0 if unused
	uint32 retval;		//  0 if unused
	const char *name;	//  NULL if unused, else pointer to a real C string
};

void Usage() {
  fprintf(stderr, "Usage: tracereader <file name>\n");
}

int main (int argc, const char** argv) {
	if (argc < 2) {Usage(); return 0;}
	const char* filename = argv[1];

	ifstream instream (filename, std::ifstream::binary);
	//ifstream infilemyfile.open (filename, ios::in | ios::binary);

	if(instream){
		// get length of file:
    	instream.seekg (0, instream.end);
    	long length = instream.tellg();
    	instream.seekg (0, instream.beg);
	
		//uint64 buffer=new uint64[1];
		char * buffer = new char [length];
		int readlength=64;
		cout << "Reading " << readlength << " bytes... ";
    	// read data as a block:
    	instream.read (buffer,readlength);
    	if (instream){
      		cout << "all bytes read successfully." << endl;
      		
      		cout << "read : " << out << endl;
      	}
    	else
      		cout << "error: only " << instream.gcount() << " could be read";
    	instream.close();

    	delete[] buffer;
		//char * buffer = new char [length];
	}
	return 0;
}


