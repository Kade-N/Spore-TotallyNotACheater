#include "stdafx.h"
#include "AchievementsManagerCheat.h"

AchievementsManagerCheat::AchievementsManagerCheat()
{
}


AchievementsManagerCheat::~AchievementsManagerCheat()
{
}


void AchievementsManagerCheat::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
	auto player = Simulator::GetPlayer();

	if (line.HasFlag("enable"))
	{
		Pollinator::cAchievementsManager::Get()->mIsCheater = false;
		if(player)
			player->mHasCheated = false;
	}
	if (line.HasFlag("disable"))
	{
		Pollinator::cAchievementsManager::Get()->mIsCheater = true;
		if (player)
			player->mHasCheated = true;
	}
	App::ConsolePrintF("Achievements are currently %s", Pollinator::cAchievementsManager::Get()->mIsCheater ? "disabled, you cheater!" : "enabled");

	if (player)
	{
		App::ConsolePrintF("When loading this save, achievements will be %s", Simulator::GetPlayer()->mHasCheated ? "disabled, you cheater!" : "enabled");
	}
}

const char* AchievementsManagerCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Checks if achievements are enabled";
	}
	else {
		return "Checks if achievements are enabled. Use -enable or -disable to enable or disable achievements.";
	}
}
