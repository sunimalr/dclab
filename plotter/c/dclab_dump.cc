// Little program to dump raw dclab trace files
// dick sites 2016.10.11
//

// 100ns granularity + call return durations
// Manupa & Sunimal 2016.10.17


#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <stdlib.h>     // exit
#include <string.h>
#include <time.h>
#include <unistd.h>     // getpid gethostname
#include <sys/time.h>   // gettimeofday
#include <sys/types.h>

#include "basetypes.h"
#include "dclab_control_names.h"


#define TRACE_OFF 0
#define TRACE_ON 1
#define TRACE_FLUSH 2
#define TRACE_RESET 3
#define TRACE_STAT 4
#define TRACE_GETCOUNT 5
#define TRACE_GETWORD 6
#define TRACE_INSERT1 7
#define TRACE_INSERTN 8

#define NopNum           0x000
#define RdtscNum         0x001
#define GetTODNum        0x002
#define VarlenLoNum      0x010
#define VarlenHiNum      0x1FF

// Variable-length starting numbers. 
// Middle hex digit will become 1..8
#define FileNameNum      0x001
#define PidNameNum       0x002
#define MethodNameNum    0x003
#define TrapNameNum      0x004
#define InterruptNameNum 0x005
#define Syscall64NameNum 0x008
#define Syscall32NameNum 0x00C
#define PacketsNum       0x100

#define UserPidNum       0x200
#define RpcidReqNum      0x201
#define RpcidRespNum     0x202
#define RpcidMidNum      0x203
#define RpcidPktNum      0x204
#define LockWaitNum      0x205
#define RunnableNum      0x206
#define IPINum           0x207

#define TrapNum          0x400
#define InterruptNum     0x500
#define TrapRetNum       0x600
#define InterruptRetNum  0x700
#define Syscall64Num     0x800
#define Syscall64RetNum  0xA00
#define Syscall32um      0xC00
#define Syscall32RetNum  0xE00

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;
using std::set;

// Number of u64 values per trace block
static const int kTraceBufSize = 8192;

typedef long long unsigned int u64;

typedef map<u64, string> U64toString;

static const char* const kNameName[16] = {
  "000", "001", "pid", "003", 
  "Trap", "Irq", "Trap", "Irq",
  "Syscall", "Syscall", "Syscall", "Syscall",
  "Syscall32", "Syscall32", "Syscall32", "Syscall32",
};

// These all use a single static buffer. In real production code, these would 
// all be std::string values, or something else at least as safe.
static const int kMaxDateTimeBuffer = 32;
static char gTempDateTimeBuffer[kMaxDateTimeBuffer];

static const int kMaxPrintBuffer = 256;
static char gTempPrintBuffer[kMaxPrintBuffer];

struct traceblock_t{
	u64 t;
	u64 block;
};

struct less_than_traceblock_t{
	inline bool operator()(traceblock_t t1, traceblock_t t2){
		return (t1.t < t2.t);
	}
};


// Turn seconds since the epoch into date_hh:mm:ss
// Not valid after January 19, 2038
const char* FormatSecondsDateTime(int32 sec) {
  if (sec == 0) {return "unknown";}  // Longer spelling: caller expecting date
  time_t tt = sec;
  struct tm* t = localtime(&tt);
  sprintf(gTempDateTimeBuffer, "%04d-%02d-%02d_%02d:%02d:%02d", 
         t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, 
         t->tm_hour, t->tm_min, t->tm_sec);
  return gTempDateTimeBuffer;
}

// Turn usec since the epoch into date_hh:mm:ss.usec
const char* FormatUsecDateTime(int64 us) {
  if (us == 0) {return "unknown";}  // Longer spelling: caller expecting date
  int32 seconds = us / 1000000;
  int32 usec = us - (seconds * 1000000);
  snprintf(gTempPrintBuffer, kMaxPrintBuffer, "%s.%06d", 
           FormatSecondsDateTime(seconds), usec);
  return gTempPrintBuffer;
}

int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

u64 nanoSeconds(u64 sec, u64 decimalsec){
	return sec*ipow(10,9) + decimalsec*100;
}

//
// Usage: dclab_dump <trace file name>
//
int main (int argc, const char** argv) {
  u64 traceblock[kTraceBufSize];

  // u64 currRDSTC = -1;
  // u64 prevRDSTC = -1;
  // u64 currentTime = -1;
  // u64 prevTime = -1;
  u64 cycle256Period = 0;

  u64 current_cpu;
  U64toString names;

  // Initialize idle process name, pid 0
  names[0x10000] = string("-idle-");
 
  FILE* f = fopen(argv[1], "rb");
  if (f == NULL) {
    fprintf(stderr, "%s did not open\n", argv[1]);
    exit(0);
  }

  string outFileName = string(argv[1]);
  outFileName += "_output.csv";
  FILE* fout = fopen(outFileName.c_str(),"wb");
  if (fout == NULL) {
    fprintf(stderr, "%s_output.csv did not open\n", argv[1]);
    exit(0);
  }

  double sigmaX = 0;
  double sigmaY = 0;
  double sigmaXY = 0;
  double N = 0;
  double sigmaX2 = 0;
  double x=0;
  double y=0;
  double denom = 0;
  double nom = 0;
  double initTime = -1;
  double initCycle = -1;
  //Calculate Regresssion Line, X = cycles; Y = time
  while (fread(traceblock, 1, sizeof(traceblock), f) != 0) {
	  if(initTime == -1){
		  initTime = traceblock[1];
		  initCycle = traceblock[0] & 0x00ffffffffffffff;
	  }
      y = traceblock[1] - initTime;
      x = (traceblock[0] & 0x00ffffffffffffff) - initCycle;
      sigmaX += x;
      sigmaY += y;
      sigmaXY += x*y;
      sigmaX2 += x*x;
      N++;
  }

  double scale = 1;
  sigmaX = sigmaX/scale;
  sigmaY = sigmaY/scale;
  sigmaXY = sigmaXY/(scale*scale);
  sigmaX2 = sigmaX2/(scale*scale);

  fprintf(stdout, "sigmaX = %f\n", sigmaX);
  fprintf(stdout, "sigmaY = %f\n", sigmaY);
  fprintf(stdout, "sigmaXY = %f\n", sigmaXY);
  fprintf(stdout, "sigmaX2 = %f\n", sigmaX2);
  fprintf(stdout, "N = %f\n", N);

  // Slope(b) = (NΣXY - (ΣX)(ΣY)) / (NΣX2 - (ΣX)2)
  denom = (N*sigmaX2 - (sigmaX*sigmaX));
  nom = (N*sigmaXY - sigmaX*sigmaY);
  fprintf(stdout, "denom = %f\n", denom);
  fprintf(stdout, "nom = %f\n", nom);

  cycle256Period =  (u64)(nom*256.0*1000/denom);
  if(cycle256Period == 0){
	  cycle256Period = 73;
	  fprintf(stdout, "256 Cycles Period was zero, hence setting to %lld\n", cycle256Period);
  }
  else{
	  fprintf(stdout, "256 Cycles Period = %lld\n", cycle256Period);
  }

  fseek(f,0,SEEK_SET);

  double time;
  u64 cycleIncrement;

  map<u64,map<u64,map<u64,pair<u64,u64> > > > eventMap;
  vector<traceblock_t> traceblocks;

  u64 currentPID = 0;
  set<u64> legalPIDs;

  if(argc == 3){
	  while (fread(traceblock, 1, sizeof(traceblock), f) != 0) {
			traceblocks.clear();
			for (int i = 2; i < kTraceBufSize; ++i) {

			  u64 n = (traceblock[i] >> 32) & 0xfff;
			  u64 arg = traceblock[i] & 0xffffffff;

			  u64 nameint, namelook;
			  nameint = ((n & 0x00f) << 8) | arg;	// For storing names
			  if ((n & 0x00f) == 2) {nameint = 0x10000 | (arg & 0xffff);}
			  namelook = n;				// For looking up names
			  if (n == 0x200) {namelook = 0x10000 | (arg & 0xffff);}

			  // Pick out any names
			  if ((0x010 <= n) && (n <= 0x1ff)) {
				// We have a name or other variable-length entry
				char tempstring[64];
				int len = (n >> 4) & 0x00f;
				if ((len < 1) || (8 < len)) {continue;}
				memset(tempstring, 0, 64);
				memcpy(tempstring, &traceblock[i + 1], (len - 1) * 8);
				fprintf(stdout, "  %s[%lld] %s\n", kNameName[n & 0x00f], arg, tempstring);
				names[nameint] = string(tempstring);
				i += (len - 1);	// Skip over the rest of the name
				continue;
			  }

			  traceblock_t temp;
			  temp.t = traceblock[i] >> 44;
			  temp.block = traceblock[i];
			  traceblocks.push_back(temp);
			}
			std::sort(traceblocks.begin(),traceblocks.end(),less_than_traceblock_t());

			for (int i = 0; i < traceblocks.size(); ++i) {
				u64 n = (traceblocks[i].block >> 32) & 0xfff;
				u64 arg = traceblocks[i].block & 0xffffffff;

				  u64 nameint, namelook;
				  nameint = ((n & 0x00f) << 8) | arg;	// For storing names
				  if ((n & 0x00f) == 2) {nameint = 0x10000 | (arg & 0xffff);}
				  namelook = n;				// For looking up names
				  namelook = n & 0b110111111111;
				  if (n == 0x200) {namelook = 0x10000 | (arg & 0xffff);}

			      string name = string("");
			      if (names.find(namelook) != names.end()) {name = names[namelook];}


				if(n == 0x200){
				  currentPID = arg & 0xffff;
				  if(name.compare(string(argv[2])) == 0){  //if a pid name is given, print those only
					  legalPIDs.insert(currentPID);
				  }
				}
			}
	  }

	  // adding min - 1 which the master thread that invokes the rest
	  u64 minPID = *std::min_element(legalPIDs.begin(),legalPIDs.end());
	  legalPIDs.insert(minPID-1);

	  fseek(f,0,SEEK_SET);
  }

  while (fread(traceblock, 1, sizeof(traceblock), f) != 0) {
    fprintf(stdout, "[0] %016llx\n", traceblock[0]);
    fprintf(stdout, "[1] %s\n", FormatUsecDateTime(traceblock[1]));
    fprintf(stdout, "      T  CPU N   ARG\n");

    time = (traceblock[1] % 1000000) * 10;

    traceblocks.clear();
    for (int i = 2; i < kTraceBufSize; ++i) {

      u64 n = (traceblock[i] >> 32) & 0xfff;
      u64 arg = traceblock[i] & 0xffffffff;

      u64 nameint, namelook;
      nameint = ((n & 0x00f) << 8) | arg;	// For storing names
      if ((n & 0x00f) == 2) {nameint = 0x10000 | (arg & 0xffff);}
      namelook = n;				// For looking up names
      if (n == 0x200) {namelook = 0x10000 | (arg & 0xffff);}

      // Pick out any names
      if ((0x010 <= n) && (n <= 0x1ff)) {
        // We have a name or other variable-length entry
        char tempstring[64];
        int len = (n >> 4) & 0x00f;
        if ((len < 1) || (8 < len)) {continue;}
        memset(tempstring, 0, 64);
        memcpy(tempstring, &traceblock[i + 1], (len - 1) * 8);
        fprintf(stdout, "  %s[%lld] %s\n", kNameName[n & 0x00f], arg, tempstring);
        names[nameint] = string(tempstring);
        i += (len - 1);	// Skip over the rest of the name
        continue;
      }

  	  traceblock_t temp;
  	  temp.t = traceblock[i] >> 44;
  	  temp.block = traceblock[i];
  	  traceblocks.push_back(temp);
    }
    std::sort(traceblocks.begin(),traceblocks.end(),less_than_traceblock_t());

    // currRDSTC=traceblock[0];
    // currentTime=traceblock[1];

    // Pick out CPU number for this traceblock
    current_cpu = traceblock[0] >> 56;
    for (int i = 0; i < traceblocks.size(); ++i) {
      // Completely skip any all-zero NOP entries
      if (traceblocks[i].block == 0) {continue;}
      
      u64 t = ((traceblocks[i].block >> 44)*cycle256Period) / 100;
      t = time + t;
      u64 tsec = (traceblock[1] / 1000000) % 60;
      u64 totalTime = tsec*10000000 + t;
      u64 n = (traceblocks[i].block >> 32) & 0xfff;
      u64 arg = traceblocks[i].block & 0xffffffff;
      pair<u64,u64> callTime;
      bool callFound = false;

      if(n == 0x200){
    	  currentPID = arg & 0xffff;
      }

      //9th bit distinguish whether its a call or return
      u64 isRet = (n >> 9) & 1;
      if(isRet == 0)
      {
        eventMap[current_cpu][currentPID][n] = make_pair(tsec,t);
      }
      else {
        // Zeroing the nine bit to make the unique idenfier
        if(eventMap[current_cpu][currentPID].find(n & 0b110111111111) != eventMap[current_cpu][currentPID].end()){
          callTime = eventMap[current_cpu][currentPID][n & 0b110111111111];
          callFound = true;
        }
        else{
          callFound = false;
        }
      }



      u64 nameint, namelook;
      nameint = ((n & 0x00f) << 8) | arg;	// For storing names
      if ((n & 0x00f) == 2) {nameint = 0x10000 | (arg & 0xffff);}
      namelook = n;				// For looking up names
      namelook = n & 0b110111111111;
      if (n == 0x200) {namelook = 0x10000 | (arg & 0xffff);}
//
//      // Pick out any names
//      if ((0x010 <= n) && (n <= 0x1ff)) {
//        // We have a name or other variable-length entry
//        char tempstring[64];
//        int len = (n >> 4) & 0x00f;
//        if ((len < 1) || (8 < len)) {continue;}
//        memset(tempstring, 0, 64);
//        memcpy(tempstring, &traceblocks[i + 1 - 2].block, (len - 1) * 8);
//        fprintf(stdout, "  %s[%lld] %s\n", kNameName[n & 0x00f], arg, tempstring);
//        names[nameint] = string(tempstring);
//        i += (len - 1);	// Skip over the rest of the name
//        continue;
//      }

      // Nothing else, so dump in hex
      string name = string("");
      if (names.find(namelook) != names.end()) {name = names[namelook];}

      if(argc == 3){
    	  if(legalPIDs.find(currentPID) == legalPIDs.end()){
    		  continue;
    	  }
      }

      if(callFound){
        fprintf(stdout, "[%3d] [%02lld.%02lld ... %02lld.%02lld] %lld %03llx %08llx %s\n", i, callTime.first, callTime.second ,tsec, t, current_cpu, n, arg, name.c_str());
        u64 difft = t - callTime.second;
        u64 difftsec = tsec - callTime.first;
        if(t < callTime.second){
        	difft = 10000000 + t - callTime.second;
        	difftsec--;
            if(tsec < callTime.first - 1){ // we are not logging events large than a minute
            	difftsec = 60 + tsec - callTime.first - 1;
            }
        }
        else{
        	if(tsec < callTime.first){ // we are not logging events large than a minute
        		difftsec = 60 + tsec - callTime.first;
        	}
        }

        fprintf(fout,"%lld,%04llx,%011lld,%011lld,%011lld,%03llx,%s\n",current_cpu, currentPID, nanoSeconds(callTime.first,callTime.second), nanoSeconds(tsec, t) , nanoSeconds(difftsec, difft) ,n, name.c_str());
      }
      else{
        fprintf(stdout, "[%3d] [               %02lld.%02lld] %lld %03llx %08llx %s\n", i, tsec, t, current_cpu, n, arg, name.c_str());
      }
    }
    fprintf(stdout, "\n");

    // prevRDSTC = currRDSTC;
    // prevTime = currentTime;
  }

  fclose(f);
  fclose(fout);
}
