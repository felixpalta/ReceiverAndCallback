#include <iostream>
#include <string>
#include <exception>
#include <fstream>

#include <io.h>
#include <fcntl.h>
#include "IReceiver.h"



using namespace std;
int main()
try
{
	IReceiver* r = createReceiver();

	// we need to open cin for binary input in order to read /r and /n symbols correctly
	if (_setmode(_fileno(stdin), _O_BINARY) == -1)
		cout << "ERROR: can't open cin to read binary" << endl;

	// input data for receiver can be of random size, not aligned to packet sizes
	// we emulate this situation by reading input data with little chunks
	const size_t CHUNK_SIZE = 5;	
	string input;	// buffer for input data
	int i = 0;
	char c;
	while ((c = (char) cin.get()) && cin){
			
			input.push_back(c);
			++i;
			//cout << c;
			if (i >= CHUNK_SIZE){
				r->receive(input.c_str(),input.size());
				input = "";
				i = 0;
			}
	}
	r->receive(input.c_str(),input.size());	// to deal with the last bytes, that didn't fit in the last chunk

	destroyReceiver(r);

}

catch (exception& e){
	cerr << e.what() << endl;

}