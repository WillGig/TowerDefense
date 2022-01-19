#pragma once

namespace TowerDefense
{
	namespace LoadingScreen
	{
		void LoadTextures(GLFWwindow* window);

		void Load(const std::string& path, std::shared_ptr<Texture> t, GLFWwindow* w);

		void RenderProgress(GLFWwindow* window, const std::string loadMessage, int loadPercent);
	}
}