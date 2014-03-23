#include <iostream>

#include "SendingImplementation.h"

void sendBinaryPacket(const char *data, unsigned int size){
	using namespace std;
	cout << "Bin: [";
	while (size-- > 0)
		cout << *data++;
	cout << "]" << endl;
}