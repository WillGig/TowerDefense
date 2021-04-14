#pragma once

namespace TowerDefense
{
	static int WIDTH = 800, HEIGHT = 600, TILESIZE = 32;
	static float SCALE = 2.0f;

	bool Init();
	void Run();
	void Stop();
	void CleanUp();

	//Sets current Game Scene (e.g. main menu, combat, base, etc.)
	void SetScene(unsigned int scene);
	
	int GetDay();
	void NextDay();
}