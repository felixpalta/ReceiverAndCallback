#include <iostream>
#include "SendingImplementation.h"

using namespace std;

// print binary packet to cin as chars, 
// because it's more demonstrative and easier to debug
void sendBinaryPacket(const char *data, unsigned int size){
	
	cout << "Bin: [";
	while (size-- > 0 && *data != '\0')
		cout << *data++;
	cout << "]" << endl;
}

// print text packet, stripped of ending to cin
void sendTextPacket(const char *data, unsigned int size){

	cout << "Text: { ";
	while (size-- > 0 && *data != '\0')
		cout << *data++;
	cout << " }" << endl;
}