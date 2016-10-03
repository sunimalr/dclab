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
#include "common.h"
#include "updateN.h"

using namespace std;

OneEvent* entry;

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
	
		//inFile.read((char*)&buf, 8);

		//uint64 * buffer= new uint64 [length];//=new uint64[1];
		int readlength=8;
		int lim=length/readlength;
		int ct=0;
		while(ct<lim){
			
			uint64 buffer;
			//char * buffer = new char [readlength];
			//cout << "Reading " << readlength << " bytes... ";
			instream.read ((char*)&buffer,readlength);
			cout << "read 8 bytes : " << buffer << endl;
			instream.seekg (0, instream.cur);
    		long test = instream.tellg();
			
			

			ct++;
		}
		
    	
    	// read data as a block:
    	
    	
    	//else
      	//	cout << "error: only " << instream.gcount() << " could be read";
    	instream.close();

    	
		//char * buffer = new char [length];
	}
	return 0;
}


