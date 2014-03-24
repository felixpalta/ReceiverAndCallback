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
	binPacket(),	
	binPacketStarted(false),
	textPacket()
	{};

	void receive(const char* data, unsigned int size);
	~Receiver()	{ destroyCallback(callbackInterface); };
private:
	ICallback* callbackInterface;

	enum {
		BINARY_START = 0x24, // start symbol of binary packet
		BINARY_SIZE = 4,	// length of binary packet
	};

 	bool binPacketStarted;

	string binPacket;	// buffer for binary packet parsing
	string textPacket;	// buffer for text packet parsing

	// returns substring for text ending packet
	const string& textEnding() const { 
		static const string s("\r\n\r\n"); 
		return s;
	} 
};

// a small helper function to compare string endings
// doesn't qualify as a member function
static bool hasEnding (std::string const &fullString, std::string const &ending);

void Receiver::receive(const char* data, unsigned int size){

	// checking one symbol per iteration
	for (unsigned int i = 0; i < size; ++i){
		if (data[i] == BINARY_START){
			binPacket = "";
			binPacketStarted = true;
			continue;
		}
		if (binPacketStarted){	
				binPacket += data[i];

			if (binPacket.size() == BINARY_SIZE) {
				binPacketStarted = false;
				callbackInterface->BinaryPacket(binPacket.c_str(),BINARY_SIZE);
			}
			continue;
		}	// if (binPacketStarted)

		// we get here only if binaryPacket isn't being parsed
		textPacket += data[i];
		if (hasEnding(textPacket,textEnding())){
			string strippedTextPacket = textPacket.substr(0,textPacket.size() - textEnding().size());
			callbackInterface->TextPacket(strippedTextPacket.c_str(),strippedTextPacket.size());
			textPacket = "";
		}
	} // for(..)
} 

IReceiver*  createReceiver(){
	IReceiver* ret = new Receiver();
	if (!ret) throw("Can't create new Receiver object");
	return ret;
}

void destroyReceiver(IReceiver* IRec){
	
	delete IRec;
}


static bool hasEnding(std::string const &fullString, std::string const &ending)	
{
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}