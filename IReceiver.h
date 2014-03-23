#pragma once


struct IReceiver{

	virtual void receive(const char* data, unsigned int size) = 0;
	virtual ~IReceiver() {};

};

IReceiver* createReceiver();

void destroyReceiver(IReceiver* IRec);
