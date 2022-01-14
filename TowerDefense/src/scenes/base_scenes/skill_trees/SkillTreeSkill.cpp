#include "pch.h"
#include "SkillTreeSkill.h"

TowerDefense::SkillTreeSkill::SkillTreeSkill(const std::string& image, std::shared_ptr<SkillTreeSkill> parent)
	:Button(0, 0, 64, 64, image), m_Applied(false), m_Parent(parent), m_Children()
{}

void TowerDefense::SkillTreeSkill::Update()
{
	if (m_Parent && !m_Parent->IsApplied())
		return;

	Button::Update();
	
	if (IsClicked())
	{
		if(!m_Applied)
			Apply();
		m_Applied = true;
	}

	if (m_Applied)
		SetSelected(true);

	for (auto child : m_Children)
		child->Update();
}

void TowerDefense::SkillTreeSkill::Render()
{
	Entity::Render();
	for (auto child : m_Children)
		child->Render();
}

void TowerDefense::SkillTreeSkill::SetPosition(float x, float y, float treeWidth)
{
	if (treeWidth < 192)
		treeWidth = 192;

	SetX(x);
	SetY(y);

	float xPos = x - treeWidth + treeWidth / ((float)m_Children.size()-0.5f);
	for (auto child : m_Children)
	{
		child->SetPosition(xPos, y - 100, treeWidth/m_Children.size());
		xPos += treeWidth / ((float)m_Children.size() - 0.5f);
	}
}