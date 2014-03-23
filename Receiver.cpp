#include <iostream>
#include <vector>
#include <string>
#include "IReceiver.h"
#include "ICallback.h"

using namespace std;

class Receiver : public IReceiver {
public:
	Receiver():
	callbackInterface(createCallback()),
	binPacket(),	// default-initialized with '\0'
	binPacketStarted(false),
	binCharIndex(0),
	textPacket(""),
	textPacketStarted(true),
	textEndingCount(0)
	{};

	void receive(const char* data, unsigned int size);
	~Receiver()	{ destroyCallback(callbackInterface); };
private:
	enum {
		BINARY_START = 0x24,
		BINARY_SIZE = 4,
	};

	ICallback* callbackInterface;

	char binPacket[BINARY_SIZE+1];	// for terminating '\0'
	bool binPacketStarted;
	unsigned binCharIndex;

	string textPacket;
	bool textPacketStarted;
	unsigned textEndingCount;
	string endingBuffer;
	const string& textEnding() const { 
		static const string s("1234"); 
		return s;
	} 
};

void Receiver::receive(const char* data, unsigned int size){

	for (unsigned int i = 0; i < size; ++i){
		if (data[i] == BINARY_START){
			binCharIndex = 0;
			binPacketStarted = true;
			continue;
		}
		if (binPacketStarted){	
				binPacket[binCharIndex++] = data[i];

			if (binCharIndex == BINARY_SIZE) {
				binPacket[BINARY_SIZE] = '\0';
				binPacketStarted = false;
				binCharIndex = 0;
				callbackInterface->BinaryPacket(binPacket,BINARY_SIZE);
			}
			continue;
		}
		// we get here only if binaryPacket isn't being parsed

		if (textEndingCount >= textEnding().size()) textEndingCount = 0;
		if (data[i] == textEnding().at(textEndingCount++)) {
			endingBuffer += data[i];
		}
		else {
			textEndingCount = 0;
			textPacket += data[i];
		}

		if (endingBuffer.size() == textEnding().size()){
			if (endingBuffer == textEnding()){
				endingBuffer = "";
				textEndingCount = 0;
				callbackInterface->TextPacket(textPacket.c_str(),textPacket.size());
				textPacket = "";

			}
			else {
				textPacket += endingBuffer;
				endingBuffer = "";
				textEndingCount = 0;
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
