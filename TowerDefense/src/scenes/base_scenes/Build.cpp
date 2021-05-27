#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/Base.h"

TowerDefense::Build::Build()
	:BaseScene("buildButton", "Create something new."),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton")),
	m_Buttons(std::make_unique<std::vector<std::shared_ptr<BuildButton>>>())
{
}

void TowerDefense::Build::Render()
{
	Player& player = Player::Get();
	player.RenderStats();
	m_Cancel->Render();

	for (unsigned int i = 0; i < m_Buttons->size(); i++)
		m_Buttons->at(i)->Render();

	player.RenderDeckAndArtifacts();
}

void TowerDefense::Build::Update()
{
	Player& player = Player::Get();

	player.UpdateDeckAndArtifacts();

	if(!player.DeckShowing() && !player.ArtifactsShowing())
	{
		for (unsigned int i = 0; i < m_Buttons->size(); i++)
		{
			m_Buttons->at(i)->Update();
			if (m_Buttons->at(i)->Clicked())
			{
				if (HasResources(m_Buttons->at(i)))
				{
					player.ChangeResource(-m_Buttons->at(i)->GetCost().w, Resource::WOOD);
					player.ChangeResource(-m_Buttons->at(i)->GetCost().x, Resource::STONE);
					player.ChangeResource(-m_Buttons->at(i)->GetCost().y, Resource::WHEAT);
					Base::AddBaseScene(m_Buttons->at(i)->GetScene());
					m_Exit = true;
					m_ActivityDone = true;
				}
			}
		}

		m_Cancel->Update();
		if (m_Cancel->IsClicked())
			m_Exit = true;
	}
}

void TowerDefense::Build::OnSwitch()
{
	BaseScene::OnSwitch();
	m_Buttons->clear();
	if (!Base::ContainsScene("Rest"))
		AddBuildButton(std::make_shared<BuildButton>("buildBed", Vec4i(100, 0, 0, 0), std::make_shared<Rest>()));
	if(!Base::ContainsScene("Library"))
		AddBuildButton(std::make_shared<BuildButton>("buildLibrary", Vec4i(400, 100, 0, 0), std::make_shared<Library>()));
	if (!Base::ContainsScene("Trader"))
		AddBuildButton(std::make_shared<BuildButton>("buildTrader", Vec4i(100, 100, 300, 0), std::make_shared<Trader>()));
	//if (!Base::ContainsScene("Fishing"))
	//	AddBuildButton(BuildButton("buildFishery", 500, std::make_shared<Fishing>()));
	if (!Base::ContainsScene("Chapel"))
		AddBuildButton(std::make_shared<BuildButton>("buildChapel", Vec4i(400, 400, 200, 0), std::make_shared<Chapel>()));
	if (!Base::ContainsScene("Smithing"))
		AddBuildButton(std::make_shared<BuildButton>("buildSmithy", Vec4i(100, 800, 100, 0), std::make_shared<Smithing>()));
	if (!Base::ContainsScene("Tavern"))
		AddBuildButton(std::make_shared<BuildButton>("buildTavern", Vec4i(500, 500, 1000, 0), std::make_shared<Tavern>()));
}

void TowerDefense::Build::AddBuildButton(std::shared_ptr<BuildButton> button)
{
	int position = m_Buttons->size();
	button->SetPosition(400.0f, 417.0f - position * 33.0f);
	m_Buttons->push_back(button);
}

bool TowerDefense::Build::HasResources(std::shared_ptr<BuildButton> b)
{
	Player& player = Player::Get();
	if (player.GetResource(Resource::WOOD) < b->GetCost().w)
		return false;
	if (player.GetResource(Resource::STONE) < b->GetCost().x)
		return false;
	if (player.GetResource(Resource::WHEAT) < b->GetCost().y)
		return false;
	return true;
}