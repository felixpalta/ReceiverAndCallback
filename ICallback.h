#pragma once
#include "IReceiver.h"

struct ICallback {

	virtual void BinaryPacket(const char* data, unsigned int size) = 0;

	virtual void TextPacket(const char* data, unsigned int size) = 0;

	virtual ~ICallback(){};

};

ICallback* createCallback();

void destroyCallback(ICallback* ICal);