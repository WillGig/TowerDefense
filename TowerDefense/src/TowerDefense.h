#pragma once

namespace TowerDefense
{
	bool Init();
	void Run();
	void Stop();
	void CleanUp();

	//Sets current Game Scene (e.g. main menu, combat, base, etc.)
	void SetScene(unsigned int scene);
	
	int GetDay();
	//For loading purposes. For all other purposes use NextDay
	void SetDay(int d);
	void NextDay();
	void ResetDay();

	bool FPSShowing();
	void ShowFPS(bool show);
	int GetFrameCap();
	void SetFrameCap(int cap);
}