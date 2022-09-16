// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "DataClass.h"
#include "SA2Enums.h"
#include "StateMachine.h"

#include <algorithm>
#include <map>
#include <vector>

bool IsHuntingStage() {
	std::vector<LevelIDs> huntingStages = { LevelIDs_WildCanyon, LevelIDs_PumpkinHill, LevelIDs_AquaticMine, LevelIDs_DeathChamber, LevelIDs_MeteorHerd,
		LevelIDs_DryLagoon, LevelIDs_EggQuarters, LevelIDs_SecurityHall, LevelIDs_MadSpace };
	if (find(huntingStages.begin(), huntingStages.end(), (LevelIDs)CurrentLevel) != huntingStages.end()) {
		return true;
	}
	return false;
}

std::string IsNG() {
	auto check = [](bool upgrade) { return (upgrade) ? " NG+" : " NG"; };

	switch ((LevelIDs)CurrentLevel) {
		case LevelIDs_PumpkinHill: {
			return check(KnucklesShovelClawGot);
		}
		case LevelIDs_DeathChamber: {
			return check(KnucklesHammerGlovesGot);
		}
		case LevelIDs_EggQuarters: {
			return check(RougePickNailsGot);
		}
		case LevelIDs_MadSpace: {
			return check(RougeIronBootsGot);
		}
		default: {
			return "";
		}
	}
}

std::string GetLevelName() {
	// There's totally a better way to do this lol
	// Probably with a macro I'm betting
	std::map<LevelIDs, std::string> idToName = { {LevelIDs_WildCanyon, "Wild Canyon"}, {LevelIDs_PumpkinHill, "Pumpkin Hill"},
		{LevelIDs_AquaticMine, "Aquatic Mine"}, {LevelIDs_DeathChamber, "Death Chamber"}, {LevelIDs_MeteorHerd, "Meteor Herd"},
		{LevelIDs_DryLagoon, "Dry Lagoon"}, {LevelIDs_EggQuarters, "Egg Quarters"}, {LevelIDs_SecurityHall, "Security Hall"}, {LevelIDs_MadSpace, "Mad Space"} };

	return idToName.at((LevelIDs)CurrentLevel) + IsNG();
}

static Data *data;
char *LevelEnd = (char *)0x174B002;

static SM oldstate;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char *path, const HelperFunctions &helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
		data = new Data();
		oldstate = SM::WaitLevel;
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		static SM state = SM::WaitLevel;
		SM nextstate;
		static int oldFrameCount = 0;
		static int frameTime = 0;
		static int newFrameTime = 0;

		switch (state) {
			case SM::WaitLevel: {
				frameTime = 0;
				newFrameTime = 0;
				if (IsHuntingStage()) {
					PrintDebug("[Hunting Data Collection] Is hunting stage\n");
					nextstate = SM::WaitLoadRestart;
				}
				else {
					nextstate = SM::WaitLevel;
				}
				break;
			}
			case SM::WaitLoadRestart: {
				// Get name of stage we're loading into
				// If we restart, we update the name
				if (oldstate != SM::WaitLoadRestart) {
					data->stageName = GetLevelName();
					PrintDebug("[Hunting Data Collection] Stage: %s\n", data->stageName.c_str());
				}

				if (ControllersEnabled && ((GameStates)GameState == GameStates_Ingame)) {
					nextstate = SM::Time;
				}
				else {
					nextstate = SM::WaitLoadRestart;
				}
				break;
			}
			case SM::Time: {
				if (*LevelEnd == 1) {
					nextstate = SM::Record;
				}

				frameTime += (FrameCount - oldFrameCount);
				newFrameTime += FrameIncrement;

				// Menu Exit
				if ((GameStates)GameState == GameStates_Inactive) {
					nextstate = SM::WaitExit;
				}
				else {
					nextstate = SM::Time;
				}
				break;
			}
			case SM::Record: {
				double ms_tmp = frameTime * 5.0 / 0.3;
				int sec = ((int)ms_tmp / 1000) % 60;
				int min = ((int)ms_tmp / (1000 * 60)) % 60;
				int ms = (int)ms_tmp % 1000;

				PrintDebug("[Hunting Data Collection] Stage time: %02d:%02d.%03d", min, sec, ms);

				ms_tmp = newFrameTime * 5.0 / 0.3;
				sec = ((int)ms_tmp / 1000) % 60;
				min = ((int)ms_tmp / (1000 * 60)) % 60;
				ms = (int)ms_tmp % 1000;

				PrintDebug("[Hunting Data Collection] Stage time v2: %02d:%d.%03d", min, sec, ms);

				PrintDebug("[Hunting Data Collection] IGT: %d:%d.%d", (int)TimerMinutes, (int)TimerSeconds, (int)((double)TimerFrames*5.0 / 0.3));

				nextstate = SM::WaitExit;
				break;
			}
			case SM::WaitExit: {
				if ((LevelIDs)CurrentLevel == LevelIDs_BasicTest) {
					nextstate = SM::WaitLevel;
				}
				else {
					nextstate = SM::WaitExit;
				}
				break;
			}
		}
		oldstate = state;
		state = nextstate;
		oldFrameCount = FrameCount;
	}

	__declspec(dllexport) void __cdecl OnInput()
	{
		// Executed before the game processes input
	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		// Executed when the game processes input
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}