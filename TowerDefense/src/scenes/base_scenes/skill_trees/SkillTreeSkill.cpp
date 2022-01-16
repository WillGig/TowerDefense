#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"

TowerDefense::SkillTreeSkill::SkillTreeSkill(const std::string& image, const std::string& name, int cost, std::shared_ptr<SkillTreeSkill> parent)
	:Button(0, 0, 64, 64, image), m_Applied(false), m_Cost(cost), m_Name(name),
	m_InfoImage(std::make_unique<Image>("TowerInfo", 0.0f, 0.0f, 200, 180, 0.0f)),
	m_Parent(parent), m_Children(), m_InfoText(std::make_unique<Text>("", 0.0f, 0.0f, 12.0f, 190.0f))
{
	if (parent)
	{
		m_RequirementText = std::make_unique<Text>("Requires: " + parent->GetName(), 0.0f, 0.0f, 12.0f, 0.0f);
		m_RequirementText->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

void TowerDefense::SkillTreeSkill::Update()
{
	//Return if parent skill is not applied
	if (m_Parent && !m_Parent->IsApplied())
		return;

	//Return if unnaffordable
	if (!m_Applied && !HasCost())
		return;

	Button::Update();
	
	if (IsClicked())
	{
		if (!m_Applied)
		{
			Apply();
			m_Applied = true;
			Player::Get().ChangeResource(m_Cost, Resource::GOLD);
			for (auto l : m_Lines)
				l->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			for (auto child : m_Children)
				child->SetRequirementText("");
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

void TowerDefense::SkillTreeSkill::RenderInfo() const
{
	m_InfoImage->Render();
	m_InfoText->Render();
	if(m_RequirementText)
		m_RequirementText->Render();
}

void TowerDefense::SkillTreeSkill::SetPosition(float x, float y, float treeWidth)
{
	if (treeWidth < 192)
		treeWidth = 192;

	m_Lines.clear();

	SetX(x);
	SetY(y);

	if (x > 400)
	{
		m_InfoImage->SetPosition(120.0f, 110.0f, 0.0f);
		m_InfoText->SetPosition(120.0f, 160.0f, 0.0f);
		if (m_RequirementText)
			m_RequirementText->SetPosition(120.0f, 40.0f, 0.0f);
	}
	else
	{
		m_InfoImage->SetPosition(800.0f - 120.0f, 110.0f, 0.0f);
		m_InfoText->SetPosition(800.0f - 120.0f, 160.0f, 0.0f);
		if (m_RequirementText)
			m_RequirementText->SetPosition(800.0f - 120.0f, 40.0f, 0.0f);
	}

	float xPos = x - treeWidth + treeWidth / ((float)m_Children.size());
	for (auto child : m_Children)
	{
		child->SetPosition(xPos, y - 100, treeWidth/m_Children.size());
		xPos += treeWidth / ((float)m_Children.size());
		std::shared_ptr<Line> connects = std::make_shared<Line>(Vec2(x, y), Vec2(child->GetX(), child->GetY()));
		connects->SetColor(0.4f, 0.4f, 0.4f, 1.0f);
		m_Lines.push_back(connects);
	}
}

void TowerDefense::SkillTreeSkill::AddChild(std::shared_ptr<SkillTreeSkill> child) 
{ 
	m_Children.push_back(child);
}

bool TowerDefense::SkillTreeSkill::HasCost() const
{
	return Player::Get().GetResource(Resource::GOLD) > m_Cost - 1;
}

std::shared_ptr<const TowerDefense::SkillTreeSkill> TowerDefense::SkillTreeSkill::GetSelectedSkill() const
{
	if (Contains(Input::GetMouseX(), Input::GetMouseY()))
		return shared_from_this();

	for (auto skill : m_Children)
	{
		auto selected = skill->GetSelectedSkill();
		if (selected != nullptr)
			return selected;
	}

	return nullptr;
}

void TowerDefense::SkillTreeSkill::SetRequirementText(const std::string& text)
{
	m_RequirementText = std::make_unique<Text>(text, 0.0f, 0.0f, 12.0f, 0.0f);
	m_RequirementText->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}