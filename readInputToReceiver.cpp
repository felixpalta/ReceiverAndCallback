#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>     // srand, rand 
#include <time.h>  

#include "IReceiver.h"
#include "readInputToReceiver.h"

using namespace std;

void readInputToReceiver(istream& is, IReceiver* IRec){
	string input;	// buffer for input data
	size_t i = 0;
	char c;

	// input data for receiver can be of random size, not aligned to packet sizes
	// we emulate this situation by reading input data with little chunks
	srand(time(NULL));
	size_t CHUNK_SIZE = rand() % 100;	// can be any value

	while ((c = (char) is.get()) && is){

		input.push_back(c);
		++i;
		if (i >= CHUNK_SIZE){
			IRec->receive(input.c_str(),input.size());
			input = "";
			i = 0;
			CHUNK_SIZE = rand() % 100;	
		}
	}
	IRec->receive(input.c_str(),input.size());	// to deal with the last bytes, that didn't fit in the last chunk
}
