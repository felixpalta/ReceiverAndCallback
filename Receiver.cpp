#include <iostream>
#include <vector>
#include <string>
#include "IReceiver.h"
#include "ICallback.h"

using namespace std;

class Receiver : public IReceiver {
public:
	Receiver():
	callbackInterface(createCallback()) {};

	void receive(const char* data, unsigned int size);
	~Receiver()	{ destroyCallback(callbackInterface); };
private:
	enum {
		BINARY_HEADER = 0x24,
		BINARY_SIZE = 4,
	};

	ICallback* callbackInterface;
};

void Receiver::receive(const char* data, unsigned int size){
	static unsigned binCharIndex = 0;
	static char binPacket[BINARY_SIZE+1] = "";
	static bool binPacketStarted = false;

	for (unsigned int i = 0; i < size; ++i){
		if (data[i] == BINARY_HEADER){
			binCharIndex = 0;
			binPacketStarted = true;
			++i;
		}
		if (binPacketStarted){
			while (binCharIndex < BINARY_SIZE && i < size && data[i] != '\0'){
				binPacket[binCharIndex++] = data[i];
				++i;
			}

			if (binCharIndex == BINARY_SIZE) {
				binPacket[BINARY_SIZE] = '\0';
				binPacketStarted = false;
				binCharIndex = 0;
				callbackInterface->BinaryPacket(binPacket,BINARY_SIZE);
			}
		}
		

	}
}
IReceiver*  createReceiver(){
	
	return new Receiver();
}

void destroyReceiver(IReceiver* IRec){
	
	delete IRec;
}
