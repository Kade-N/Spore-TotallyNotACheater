// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "AchievementsManagerCheat.h"
#include "CheatInvokedListener.h"
#include <Spore\App\cCheatManager.h>

HMODULE modModule;

bool FileExists(string path)
{
	return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

string GetModFolderPath()
{
	char charPath[MAX_PATH];
	GetModuleFileNameA(modModule, charPath, sizeof(charPath));
	string path = charPath;

	// Remove the file name from the path
	path = path.substr(0, path.find_last_of("\\") + 1);

	return path;
}

bool IsOptionEnabled(string optionName)
{
	// Check if the file exists in the mod folder
	return FileExists(GetModFolderPath() + "TotallyNotACheater-" + optionName);
}

void Initialize()
{
	CheatManager.AddCheat("achievements", new AchievementsManagerCheat());
	
	// Optionally notify player that they've cheated
	if (IsOptionEnabled("ShowCheatMessage"))
	{
		MessageManager.AddListener(new CheatInvokedListener(), App::ICheatManager::MessageIDs::kMsgCheatInvoked);
	}
}

void Dispose()
{
	// This method is called when the game is closing
}

virtual_detour(AddCheat__detour, App::cCheatManager, App::ICheatManager, void(const char*, ArgScript::ICommand*, bool)) {
	void detoured(const char* pString, ArgScript::ICommand* pParser, bool bNotify) {
		// Setting bNotify to false prevents CheatManager from sending the kMsgCheatInvoked message, keeping achievements enabled and preventing the Joker badge
		original_function(this, pString, pParser, false);
	}
};

void AttachDetours()
{
	// Optionally remove bNotify from every cheat registered
	if (IsOptionEnabled("AllowCheating"))
	{
		AddCheat__detour::attach(GetAddress(App::cCheatManager, AddCheat));
	}
}

// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		modModule = hModule;
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

