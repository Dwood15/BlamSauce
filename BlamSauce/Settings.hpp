/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <precompile.h>

namespace Yelo::Settings {
	const char * K_CHAT_LOG_FILENAME = "Game.ChatLog.txt";
	static c_settings_manager g_settings_manager("OpenSauce");

	c_settings_manager &Manager() {
		return g_settings_manager;
	}

	/// <summary>	Initializes the shared settings. </summary>
	void InitializeSettings() {
		ReadCmdLineSettings();

		const char * profile_path = "";

		if (CMDLINE_GET_PARAM(path).ParameterSet())
			profile_path = CMDLINE_GET_PARAM(path).GetValue();

		Settings::SharedInitialize(profile_path);
	}

	/// <summary>	Disposes the shared settings. </summary>
	void DisposeSettings() {
		Settings::SharedDispose();
	}

	/// <summary>	Loads the settings from file. </summary>
	void Load() {
		char file_path[MAX_PATH];
		GetSettingsFilePath(K_USER_FILENAME_XML, file_path);
		g_settings_manager.Load(std::string(file_path));
	}

	/// <summary>	Saves the settings to file. </summary>
	void Save() {
		g_settings_manager.Save();
	}
};
