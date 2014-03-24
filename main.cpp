#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <io.h>
#include <fcntl.h>

#include "IReceiver.h"
#include "ReadCinIntoReceiver.h"


using namespace std;


int main()
try
{
	IReceiver* IRec = createReceiver();

	// we need to open cin for binary input in order to read /r and /n symbols correctly
	if (_setmode(_fileno(stdin), _O_BINARY) == -1)
		cout << "ERROR: can't open cin to read binary" << endl;

	// input data for receiver can be of random size, not aligned to packet sizes
	// we emulate this situation by reading input data with little chunks
	
	readCinIntoReceiver(IRec);

	destroyReceiver(IRec);

}

catch (exception& e){
	cerr << e.what() << endl;

}