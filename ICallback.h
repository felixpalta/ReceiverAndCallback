#pragma once
#include "IReceiver.h"

// interface for Callback class, used by Receiver
struct ICallback {

	virtual void BinaryPacket(const char* data, unsigned int size) = 0;	// send binary packet, without header

	virtual void TextPacket(const char* data, unsigned int size) = 0;	// send text packet, without ending

	virtual ~ICallback(){};

};

ICallback* createCallback();

void destroyCallback(ICallback* ICal);