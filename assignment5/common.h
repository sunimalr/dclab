

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

