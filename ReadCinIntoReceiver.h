#pragma once

#include <iostream>
#include <string>
#include "IReceiver.h"
#include "ReadCinIntoReceiver.h"

void readCinIntoReceiver(const size_t chunk_size, IReceiver* IRec);