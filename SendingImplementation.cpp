#include <iostream>
#include "SendingImplementation.h"

using namespace std;

void sendBinaryPacket(const char *data, unsigned int size){
	
	cout << "Bin: [";
	while (size-- > 0)
		cout << *data++;
	cout << "]" << endl;
}

void sendTextPacket(const char *data, unsigned int size){

	cout << "Text: { ";
	while (size-- > 0)
		cout << *data++;
	cout << " }" << endl;
}