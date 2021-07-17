#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/Base.h"

TowerDefense::Build::Build()
	:BaseScene("buildButton", "Create something new.", 0),
	m_Cancel(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "cancelButton")),
	m_Buttons(std::make_unique<std::vector<std::shared_ptr<BuildButton>>>())
{}

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
					m_Buttons->at(i)->OnPurchased();
					m_Exit = true;
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
	if (!Base::ContainsScene("ManageWorkers"))
		AddBuildButton(std::make_shared<BuildButton>("buildHouse", Vec4i(100, 100, 0, 0), std::make_shared<ManageWorkers>()));
	else
	{
		if (!Base::ContainsScene("Library"))
			AddBuildButton(std::make_shared<BuildButton>("buildLibrary", Vec4i(400, 100, 0, 0), std::make_shared<Library>()));
		if (!Base::ContainsScene("Trader"))
			AddBuildButton(std::make_shared<BuildButton>("buildTrader", Vec4i(100, 100, 300, 0), std::make_shared<Trader>()));
		if (!Base::ContainsScene("ArcheryRange"))
			AddBuildButton(std::make_shared<BuildButton>("buildArcheryRange", Vec4i(400, 100, 0, 0), std::make_shared<ArcheryRange>()));
		if (!Base::ContainsScene("MusicHall"))
			AddBuildButton(std::make_shared<BuildButton>("buildMusicHall", Vec4i(300, 100, 100, 0), std::make_shared<MusicHall>()));
		if (!Base::ContainsScene("Chapel"))
			AddBuildButton(std::make_shared<BuildButton>("buildChapel", Vec4i(400, 400, 200, 0), std::make_shared<Chapel>()));
		if (!Base::ContainsScene("Smithing"))
			AddBuildButton(std::make_shared<BuildButton>("buildSmithy", Vec4i(100, 800, 100, 0), std::make_shared<Smithing>()));
		if (!Base::ContainsScene("Tavern"))
			AddBuildButton(std::make_shared<BuildButton>("buildTavern", Vec4i(500, 500, 1000, 0), std::make_shared<Tavern>()));
		if (!Player::Get().HasArtifact("Magical Generator"))
			AddBuildButton(std::make_shared<ArtifactBuildButton>("buildMagicalGenerator", Vec4i(300, 300, 300, 0), std::make_shared<MagicalGenerator>()));
		else
		{
			if (!Base::ContainsScene("WizardTower"))
				AddBuildButton(std::make_shared<BuildButton>("buildWizardTower", Vec4i(200, 500, 0, 0), std::make_shared<WizardTower>()));
			if (!Base::ContainsScene("Temple"))
				AddBuildButton(std::make_shared<BuildButton>("buildTemple", Vec4i(300, 300, 100, 0), std::make_shared<Temple>()));
			if (!Base::ContainsScene("AlchemyLab"))
				AddBuildButton(std::make_shared<BuildButton>("buildAlchemyLab", Vec4i(400, 300, 000, 0), std::make_shared<AlchemyLab>()));
		}
	}
}

void TowerDefense::Build::AddBuildButton(std::shared_ptr<BuildButton> button)
{
	int position = m_Buttons->size();
	button->SetPosition(400.0f, 437.0f - position * 33.0f);
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