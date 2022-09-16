// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "StateMachine.h"

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char *path, const HelperFunctions &helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		static SM state = SM::WaitLevel;

		switch (state) {
			case SM::WaitLevel: {

			}
			case SM::WaitLoadRestart: {

			}
			case SM::Time: {

			}
			case SM::Record: {

			}
			case SM::WaitExit: {
			
			}
		}
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