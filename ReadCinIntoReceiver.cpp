#include <iostream>
#include <string>
#include "IReceiver.h"
#include "ReadCinIntoReceiver.h"

using namespace std;

void readCinIntoReceiver(const size_t chunk_size, IReceiver* IRec){
	string input;	// buffer for input data
	size_t i = 0;
	char c;
	while ((c = (char) cin.get()) && cin){

		input.push_back(c);
		++i;
		if (i >= chunk_size){
			IRec->receive(input.c_str(),input.size());
			input = "";
			i = 0;
		}
	}
	IRec->receive(input.c_str(),input.size());	// to deal with the last bytes, that didn't fit in the last chunk
}
