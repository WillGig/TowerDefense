#pragma once
#include "Artifact.h"

namespace TowerDefense
{
	class ArtifactPile : public Button
	{
	public:
		ArtifactPile(float x, float y);

		void Update() override;

		void RenderArtifacts();

		void AddArtifact(std::shared_ptr<Artifact> a);

		std::shared_ptr<Artifact> RemoveArtifact(int index);

		std::shared_ptr<Artifact> GetSelectedArtifact();

		bool HasArtifact(const std::string& name);

		void Clear();

		inline std::shared_ptr<Artifact> GetArtifact(int index) const { return m_Artifacts->at(index); }

		inline void Show(bool showing) { m_Showing = showing; }

		inline bool IsShowing() const { return m_Showing; }

		inline int GetSize() const { return m_Artifacts->size(); }

	private:
		void UpdatePositions();

		int m_SelectedArtifact;

		bool m_Showing;

		std::unique_ptr<std::vector<std::shared_ptr<Artifact>>> m_Artifacts;

		//Fade background when rendering artifact list
		std::unique_ptr<Rectangle> m_Fade;
	};
}