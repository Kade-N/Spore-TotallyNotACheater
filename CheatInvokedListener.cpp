#include "stdafx.h"
#include "CheatInvokedListener.h"

CheatInvokedListener::CheatInvokedListener()
{
}


CheatInvokedListener::~CheatInvokedListener()
{
}

// For internal use, do not modify.
int CheatInvokedListener::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int CheatInvokedListener::Release()
{
	return DefaultRefCounted::Release();
}


// The method that receives the message. The first thing you should do is checking what ID sent this message...
bool CheatInvokedListener::HandleMessage(uint32_t messageID, void* message)
{
	if (messageID == App::ICheatManager::MessageIDs::kMsgCheatInvoked)
	{
		App::ConsolePrintF("You've cheated!");
	}
	// Return true if the message has been handled. Other listeners will receive the message regardless of the return value.
	return false;
}
