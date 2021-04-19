#pragma once

namespace TowerDefense
{
	static int WIDTH = 1600, HEIGHT = 1200, TILESIZE = 32;

	bool Init();
	void Run();
	void Stop();
	void CleanUp();

	//Sets current Game Scene (e.g. main menu, combat, base, etc.)
	void SetScene(unsigned int scene);
	
	int GetDay();
	void NextDay();
}