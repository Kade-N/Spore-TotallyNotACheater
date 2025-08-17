# Spore Mod: Totally Not A Cheater
Allows enabling or disabling achievements, as well as optionally preventing cheats from disabling achievements and granting the Joker badge.

## Installation Instructions
Download the .sporemod file from [Releases](https://github.com/Kade-N/Spore-TotallyNotACheater/releases) and install it using the Spore ModAPI Easy Installer, part of the [Spore ModAPI Launcher Kit](https://launcherkit.sporecommunity.com/).

## Mod Details
### Achievements Cheat
Spore tracks whether achievements are *currently* enabled as a simple boolean value. Additionally, each save game stores a separate boolean value, indicating whether the player has cheated while inside that particular save. Upon loading the save planet, the main boolean is changed to match the one stored in the save data. This cheat shows and changes *both* values.

- `achievements` shows whether achievements are currently enabled.
- `achievements -enable` will change the values so that achievements can be earned, as if the player has *not* cheated.
- `achievements -disable` will change the values so that achievements cannot be earned, as if the player has cheated.

At a technical level, this is a very simple cheat that gets or sets the value of the following two booleans:
- [Pollinator::cAchievementsManager::mIsCheater](https://emd4600.github.io/Spore-ModAPI/class_pollinator_1_1c_achievements_manager.html#ac2dd55a444acf6e8082edbab257dbd63) - controls if achievements are currently enabled
- [Simulator::cPlayer::mHasCheated](https://emd4600.github.io/Spore-ModAPI/class_simulator_1_1c_player.html#a450ec039eec0de14e0d2a82df8b0116c) - stored per-save to determine whether achievements are enabled or disabled upon loading the save planet

### Show Cheat Message
If this option is enabled, a "You've cheated!" message will show in the console after a cheat that disables achievements has been used. This serves purely to inform the player that achievements are now disabled.

At a technical level, this uses a [message listener](https://emd4600.github.io/Spore-ModAPI/_messaging.html) to listen for the [kMsgCheatInvoked](https://emd4600.github.io/Spore-ModAPI/class_app_1_1_i_cheat_manager.html#a97efda0f36e8432bb2c2c189490fd375a9db74e3e92fee3e67fb0fe6c7eaafe25) message that is sent by App::cCheatManager.

### Allow Cheating
If this option is enabled, cheats will never disable achievements at all. This also prevents the Joker badge from being awarded in space stage.

It does not retroactively re-enable achievements in existing save planets (use the `achievements -enable` to do this, as explained above). It also does not remove the Joker badge if already awarded - badge management is outside the scope of this mod.

At a technical level, this uses a detour on [App::ICheatManager::AddCheat](https://emd4600.github.io/Spore-ModAPI/class_app_1_1_i_cheat_manager.html#a986338701bb3cab32eea2e73dc5cbfa7). This function is called by both the game's own code, as well as other mods, to register cheats for use in the console. The bNotify parameter controls whether the cheat disables achievements. The detour simply overrides the parameter set by the game or other mods, setting all cheats so they do not disable achievements.

Because the "Show Cheat Message" option only shows a message when achievements have been disabled, the messages will never be triggered if this option is also enabled - because achievements will not be disabled. This is intended behaviour.