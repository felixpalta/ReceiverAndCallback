#pragma once

// interface for Receiver class
// Parses incoming data for two kinds of packets
// -binary packet
// - text packet
struct IReceiver{

	virtual void receive(const char* data, unsigned int size) = 0;
	virtual ~IReceiver() {};

};

IReceiver* createReceiver();

void destroyReceiver(IReceiver* IRec);
