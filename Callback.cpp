#include "ICallback.h"
#include "IReceiver.h"
#include "SendingImplementation.h"

class Callback : public ICallback {
public:
	Callback(){};
private:
	void BinaryPacket(const char* data, unsigned int size);

	void TextPacket(const char* data, unsigned int size);

	~Callback(){};
};

void Callback::BinaryPacket(const char* data, unsigned int size){
	sendBinaryPacket(data,size);
}

void Callback::TextPacket(const char* data, unsigned int size){
	sendTextPacket(data,size);
}

ICallback* createCallback(){
	return new Callback();
}

void destroyCallback(ICallback* ICal){
	delete ICal;
}