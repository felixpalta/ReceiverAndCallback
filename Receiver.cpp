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
	textPacket()
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

	const string& textEnding() const { 
		static const string s("\r\n\r\n"); 
		return s;
	} 
};

// a small helper function to compare string endings
// doesn't qualify as a member function
static bool hasEnding (std::string const &fullString, std::string const &ending);

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
		textPacket += data[i];
		if (hasEnding(textPacket,textEnding())){
			string strippedTextPacket = textPacket.substr(0,textPacket.size() - textEnding().size());
			callbackInterface->TextPacket(strippedTextPacket.c_str(),strippedTextPacket.size());
			textPacket = "";
		}
	}
}

IReceiver*  createReceiver(){
	IReceiver* ret = new Receiver();
	if (!ret) throw("Can't create new Receiver object");
	return ret;
}

void destroyReceiver(IReceiver* IRec){
	
	delete IRec;
}


static bool hasEnding (std::string const &fullString, std::string const &ending)	
{
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}