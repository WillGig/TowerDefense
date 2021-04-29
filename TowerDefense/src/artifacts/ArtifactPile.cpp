#include "pch.h"
#include "ArtifactPile.h"

TowerDefense::ArtifactPile::ArtifactPile(float x, float y)
	:Button(x, y, 50, 50, "viewArtifactsButton"),
	m_SelectedArtifact(-1), m_Showing(false),
	m_Artifacts(std::make_unique<std::vector<std::shared_ptr<Artifact>>>()), 
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
}

void TowerDefense::ArtifactPile::Update()
{
	if(m_SelectedArtifact == -1)
		Button::Update();

	if (IsClicked())
		m_Showing = !m_Showing;

	if (m_Showing) {
		//Check for Selected Artifact
		for (int i = 0; i < (int)m_Artifacts->size(); i++) 
		{
			if (m_SelectedArtifact != -1)
				continue;
			if (m_Artifacts->at(i)->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
				m_SelectedArtifact = i;
		}

		//Check if clicked off of Selected Artifact
		if (m_SelectedArtifact != -1 && Input::GetRightMouseClickedAndSetFalse() || Input::GetLeftMouseClickedAndSetFalse())
			m_SelectedArtifact = -1;
	}
}

void TowerDefense::ArtifactPile::RenderArtifacts()
{
	m_Fade->Render();
	for (unsigned int i = 0; i < m_Artifacts->size(); i++) {
		m_Artifacts->at(i)->Render();
	}
	if (m_SelectedArtifact != -1)
	{
		m_Fade->Render();
		m_Artifacts->at(m_SelectedArtifact)->RenderArtifactDetails();
	}
}

void TowerDefense::ArtifactPile::AddArtifact(std::shared_ptr<Artifact> a)
{
	a->SetY(500.0f - 50 * (m_Artifacts->size() / 10));
	a->SetX(400.0f - ((m_Artifacts->size() / 10) * 10 + 4.5f - m_Artifacts->size()) * 67.0f);
	m_Artifacts->push_back(a);
}

std::shared_ptr<TowerDefense::Artifact> TowerDefense::ArtifactPile::RemoveArtifact(int index)
{
	std::shared_ptr<Artifact> returner = m_Artifacts->at(index);
	m_Artifacts->erase(m_Artifacts->begin() + index);
	UpdatePositions();
	return returner;
}

std::shared_ptr<TowerDefense::Artifact> TowerDefense::ArtifactPile::GetSelectedArtifact()
{
	if (m_SelectedArtifact == -1)
		return nullptr;
	return m_Artifacts->at(m_SelectedArtifact);
}

void TowerDefense::ArtifactPile::Clear()
{
	m_Artifacts->clear();
}

void TowerDefense::ArtifactPile::UpdatePositions()
{
	for (int i = 0; i < (int)m_Artifacts->size(); i++) {
		m_Artifacts->at(i)->SetY(500.0f - 50 * (i / 10));
		m_Artifacts->at(i)->SetX(400.0f - ((i / 10) * 10 + 4.5f - i) * 67.0f);
	}
}