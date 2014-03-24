#include <iostream>
#include <string>
#include <stdlib.h>     // srand, rand 
#include <time.h>  

#include "IReceiver.h"
#include "ReadCinIntoReceiver.h"

using namespace std;

void readCinIntoReceiver( IReceiver* IRec){
	string input;	// buffer for input data
	size_t i = 0;
	char c;

	srand(time(NULL));
	size_t CHUNK_SIZE = rand() % 100;	// can be any value

	while ((c = (char) cin.get()) && cin){

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
