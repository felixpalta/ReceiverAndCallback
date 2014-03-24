#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <io.h>
#include <fcntl.h>

#include "IReceiver.h"
#include "readInputToReceiver.h"


using namespace std;


int main(int argc, char* argv[])
try
{
	if (argc < 2) 
		throw exception("Expected input file name as a parameter");

	string filename(argv[1]);
	ifstream ifs(filename.c_str(),ios::binary);

	if (!ifs) throw exception(("Can't open file: " + filename).c_str());

	IReceiver* IRec = createReceiver();	// createReceiver either returns non-NULL pointer or throws
	
	readInputToReceiver(ifs,IRec);

	destroyReceiver(IRec);

}

catch (exception& e){
	cerr << e.what() << endl;

}