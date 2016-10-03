//author : Sunimal Rathnayake
//date : 2016.10.04

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
#include "parse.h"
#include "print.h"
#include <vector>

using namespace std;

void Usage() {
  fprintf(stderr, "Usage: tracereader <file name>\n");
}

int main (int argc, const char** argv) {

	int cpu;
	uint64 cycle_counter;
	uint64 gettimeofday_val;
	std::map<uint32,std::map<uint32,const char *> > name_map; 
	std::map<uint64,OneEvent> unpaired_entry_map;	

	if (argc < 2) {Usage(); return 0;}
	const char* filename = argv[1];

	OneEvent *entry;
	entry = (OneEvent *) malloc (sizeof(OneEvent));
	entry->t=1000;
	entry->duration=0;
	entry->cpu=0;
	entry->type=0xffff;
	entry->number=0;
	entry->rpcid=0;
	entry->arg0=0;
	entry->return_t=0;
	entry->retval=0;
	entry->name=NULL;
	
	ifstream instream (filename, std::ifstream::binary);
	
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
				//cout << "cpu : " << cpu << " cycle_counter : " << cycle_counter << endl;
				entry->cpu=cpu;
				ct++;
				continue;
			}

			if(ct==1){
				gettimeofday_val=buffer;
				//cout << "gettimeofday_val : " << gettimeofday_val << endl;
				ct++;
				continue;
			}

			//cout << "read 8 bytes : " << buffer << endl;
			instream.seekg (0, instream.cur);
    		long test = instream.tellg();
			
			//Update N
			uint64 N;
			N=updateN(entry,buffer);
			//if type=0x100, then need to read more entries as the name field. 
			//Putting the to a vector.
			//cout<<hex<<"N :: "<<N<<endl;
			//cout<<dec<<"T :: "<<entry->t<<endl;
			//cout << entry->type << endl;

			if(entry->type == 0x100){
				//get number of uint64s to read
				int no_of_words_to_read=(N>>4) & 0x000000000000000f;
				//cout << "no_of_words_to_read : " << no_of_words_to_read << endl;
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
				updateName(entry,v,&name_map);
				//cout << entry->name <<endl;
			}
			uint64 argret_code;
			argret_code=updateArgRet(entry,buffer);
			//if 0x2, unpaired, 0 paired, -1 not relevant

			uint64 N_map;
			
			//if argret_code is 0x2, the entry is an unpaired one
			if(argret_code == 0x2){
				uint64 switchval_digit3=N >> 8;
				uint64 temp=N & 0x0ff;
				switch (switchval_digit3) {
  					case 0xA:
  						N_map=temp | 0x800;
  						break;
  					case 0xB:
  						N_map=temp | 0x900;
  						break;
  					case 0xE:
  						N_map=temp | 0xC00;
  						break;
  					case 0xF:
  						N_map=temp | 0xD00;
  						break;
  					case 0x6:
  						N_map=temp | 0x400;
  						break;
  					case 0x7:
  						N_map=temp | 0x500;
  						break;
  				}
  				//cout << "N : " << hex << N << " N_MAP : " << hex << N_map<<endl;
  				//Check if the unpaired entry exists in the map. If so update it.
				if(unpaired_entry_map.find(N_map)!=unpaired_entry_map.end()){ //entry found in map
					unpaired_entry_map[N_map].retval=entry->arg0;
					unpaired_entry_map[N_map].return_t=entry->t;
					entry=&unpaired_entry_map[N_map];
					unpaired_entry_map.erase (N_map);
					//cout << " paired T : " << entry->t << endl;
					exit(0);
				}
				else if((switchval_digit3 == 0x8) || (switchval_digit3 == 0x9) || (switchval_digit3 == 0xC) || (switchval_digit3 == 0xD) || (switchval_digit3 == 0x4) || (switchval_digit3 == 0x5)){
					unpaired_entry_map[N]=*entry;
					//cout << " unpaired T : " << entry->t << endl;
				}
				
			}
			print_entry(entry, &name_map);
			ct++;
		}
			
       	instream.close();
	}
	return 0;
}


