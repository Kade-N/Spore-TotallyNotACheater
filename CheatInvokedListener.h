#pragma once

#include <Spore\BasicIncludes.h>

#define CheatInvokedListenerPtr intrusive_ptr<CheatInvokedListener>

class CheatInvokedListener 
	: public App::IMessageListener
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("CheatInvokedListener");

	CheatInvokedListener();
	~CheatInvokedListener();

	int AddRef() override;
	int Release() override;
	
	// This is the function you have to implement, called when a message you registered to is sent.
	bool HandleMessage(uint32_t messageID, void* message) override;
};
