#pragma once

namespace TowerDefense
{
	namespace Save
	{
		static int SaveSlot;

		void SaveSettings();
		void SaveGame(int slot);
	}

	namespace Load
	{
		void LoadSettings();
		void LoadGame(int slot);
	}
}