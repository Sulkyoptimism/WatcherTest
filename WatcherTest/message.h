#pragma once
#include "include/oscpp/client.hpp"
#include "include/oscpp/util.hpp"
#include "RPCtransport.h"
class message
{
public: 
	bool started = false;

	void sendPacket(RPCtransport* t, void* buffer, size_t bufferSize);
	size_t makePacket(void* buffer, size_t size);
	void activate();

};

