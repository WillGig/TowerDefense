#pragma once

namespace TowerDefense
{
	namespace Save
	{
		void SaveSettings();
		void SaveGame(int slot);
	}

	namespace Load
	{
		void LoadSettings();
		void LoadGame(int slot);
	}
}