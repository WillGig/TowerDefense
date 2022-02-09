#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"

TowerDefense::SkillTreeSkill::SkillTreeSkill(const std::string& image, const std::string& name, std::shared_ptr<SkillTreeSkill> parent)
	:Button(0, 0, 64, 64, image), m_Applied(false), m_Name(name),
	m_InfoImage(std::make_unique<Image>("TowerInfo", 0.0f, 0.0f, 200, 180, 0.0f)),
	m_Parent(parent), m_Children(), m_NameText(std::make_unique<Text>(name, 0.0f, 0.0f, 12.0f, 190.0f)),
	m_InfoText(std::make_unique<Text>("", 0.0f, 0.0f, 12.0f, 190.0f))
{
	if (parent)
	{
		m_RequirementText = std::make_unique<Text>("Need: " + parent->GetName(), 0.0f, 0.0f, 10.0f, 0.0f);
		m_RequirementText->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

void TowerDefense::SkillTreeSkill::Update()
{
	//Return if parent skill is not applied
	if (m_Parent && !m_Parent->IsApplied())
		return;

	Button::Update();

	if (IsClicked())
	{
		if (!m_Applied)
		{
			Apply();
			m_Applied = true;
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
	m_NameText->Render();
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
		m_NameText->SetPosition(120.0f, 180.0f, 0.0f);
		m_InfoImage->SetPosition(120.0f, 110.0f, 0.0f);
		m_InfoText->SetPosition(120.0f, 130.0f, 0.0f);
		if (m_RequirementText)
			m_RequirementText->SetPosition(120.0f, 40.0f, 0.0f);
	}
	else
	{
		m_NameText->SetPosition(800.0f - 120.0f, 180.0f, 0.0f);
		m_InfoImage->SetPosition(800.0f - 120.0f, 110.0f, 0.0f);
		m_InfoText->SetPosition(800.0f - 120.0f, 130.0f, 0.0f);
		if (m_RequirementText)
			m_RequirementText->SetPosition(800.0f - 120.0f, 40.0f, 0.0f);
	}

	float spacing = 0;
	if(m_Children.size() > 1)
		spacing = treeWidth / (float)(m_Children.size() - 1);

	float xPos = x - ((m_Children.size() - 1) / 2.0f) * spacing;
	for (auto child : m_Children)
	{
		child->SetPosition(xPos, y - 100, treeWidth/m_Children.size());
		xPos += spacing;
		std::shared_ptr<Line> connects = std::make_shared<Line>(Vec2(x, y), Vec2(child->GetX(), child->GetY()));
		connects->SetColor(0.4f, 0.4f, 0.4f, 1.0f);
		m_Lines.push_back(connects);
	}
}

void TowerDefense::SkillTreeSkill::AddChild(std::shared_ptr<SkillTreeSkill> child) 
{ 
	m_Children.push_back(child);
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
	m_RequirementText = std::make_unique<Text>(text, 0.0f, 0.0f, 10.0f, 0.0f);
	m_RequirementText->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}

const std::string TowerDefense::SkillTreeSkill::GetSkillsSelected() const
{
	std::string value;

	if (m_Applied)
		value = "1";
	else
		value = "0";

	for (auto child : m_Children)
		value += child->GetSkillsSelected();

	return value;
}

void TowerDefense::SkillTreeSkill::SetSkillsSelected(const std::string& selected)
{
	char applied = selected[0];
	if (applied == '1')
	{
		m_Applied = true;
		for (auto l : m_Lines)
			l->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		for (auto child : m_Children)
			child->SetRequirementText("");
	}

	std::string current = selected;
	for (auto child : m_Children)
	{
		child->SetSkillsSelected(current.substr(1, child->GetNumInTree()));
		current = current.substr(child->GetNumInTree());
	}
}

int TowerDefense::SkillTreeSkill::GetNumInTree() const
{
	if (m_Children.size() == 0)
		return 1;

	int num = 1;

	for (auto child : m_Children)
		num += child->GetNumInTree();

	return num;
}

int TowerDefense::SkillTreeSkill::GetNumApplied() const
{
	if (!m_Applied)
		return 0;

	if (m_Children.size() == 0)
		return 1;

	int num = 1;

	for (auto child : m_Children)
		num += child->GetNumApplied();

	return num;
}