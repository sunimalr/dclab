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
#include <vector>

using namespace std;

void Usage() {
  fprintf(stderr, "Usage: tracereader <file name>\n");
}

int main (int argc, const char** argv) {

	int cpu;
	uint64 cycle_counter;
	uint64 gettimeofday_val;

	if (argc < 2) {Usage(); return 0;}
	const char* filename = argv[1];

	OneEvent *entry;
	entry = (OneEvent *) malloc (sizeof(OneEvent));
	
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
			instream.read ((char*)&buffer,readlength);

			if(ct==0){
				cpu=(buffer>>56) & 0x00000000000000ff;
				cycle_counter=buffer & 0x00ffffffffffffff;
				cout << "cpu : " << cpu << " cycle_counter : " << cycle_counter << endl;
				ct++;
				continue;
			}

			if(ct==1){
				gettimeofday_val=buffer;
				cout << "gettimeofday_val : " << gettimeofday_val << endl;
				ct++;
				continue;
			}

			cout << "read 8 bytes : " << buffer << endl;
			instream.seekg (0, instream.cur);
    		long test = instream.tellg();
			
			//Update N
			uint64 N;
			N=updateN(entry,buffer);
			//if type=0x100, then need to read more entries as the name field. 
			//Putting the to a vector.
			cout << entry->type << endl;

			if(entry->type == 0x100){
				//get number of uint64s to read
				int no_of_words_to_read=(N>>4) & 0x000000000000000f;
				cout << "no_of_words_to_read : " << no_of_words_to_read << endl;
				std::vector<uint64> v;
				//no_of_words_to_read is inclusive of current word
				no_of_words_to_read--;
				v.push_back(buffer);

				//read the rest of the words for the vector
				int wcount=0;
				for(wcount=0 ; wcount < no_of_words_to_read ; wcount++){
					instream.read ((char*)&buffer,readlength);
					v.push_back(buffer);
					ct++;
				}
			}
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


