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
		if (!m_Applied)
		{
			Apply();
			m_Applied = true;
			for (std::shared_ptr<Line> l : m_Lines)
				l->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	if (m_Applied)
		SetSelected(true);

	for (auto child : m_Children)
		child->Update();
}

void TowerDefense::SkillTreeSkill::Render()
{
	for (std::shared_ptr<Line> l : m_Lines)
		l->Render();

	Entity::Render();

	for (auto child : m_Children)
		child->Render();
}

void TowerDefense::SkillTreeSkill::SetPosition(float x, float y, float treeWidth)
{
	if (treeWidth < 192)
		treeWidth = 192;

	m_Lines.clear();

	SetX(x);
	SetY(y);

	float xPos = x - treeWidth + treeWidth / ((float)m_Children.size()-0.5f);
	for (auto child : m_Children)
	{
		child->SetPosition(xPos, y - 100, treeWidth/m_Children.size());
		xPos += treeWidth / ((float)m_Children.size() - 0.5f);
		std::shared_ptr<Line> connects = std::make_shared<Line>(Vec2(x, y), Vec2(child->GetX(), child->GetY()));
		connects->SetColor(0.4f, 0.4f, 0.4f, 1.0f);
		m_Lines.push_back(connects);
	}
}

void TowerDefense::SkillTreeSkill::AddChild(std::shared_ptr<SkillTreeSkill> child) 
{ 
	m_Children.push_back(child);
}