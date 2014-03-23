#include "IReceiver.h"

class Receiver : public IReceiver {
public:
	Receiver(): data() {};
	void receive(const char* data, unsigned int size){};
	~Receiver(){};
private:
	char* data;
};

IReceiver*  createReceiver(){
	return new Receiver();
}