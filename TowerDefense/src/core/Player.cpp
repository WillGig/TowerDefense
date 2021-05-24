#include "pch.h"
#include "Player.h"
#include "scenes/Scene.h"
#include "cards/SkillCards.h"
#include "cards/AuraCards.h"
#include "cards/TowerCards.h"

TowerDefense::Player::Player()
    :m_Health(100), m_MaxHealth(100), m_Energy(100), m_Resources(0, 0, 0, 0), m_Hand(std::make_shared<Hand>(10)),
    m_Deck(std::make_shared<CardPile>(-100.0f,0.0f)), 
    m_DrawPile(std::make_shared<CardPile>(49.0f, 50.0f)),
    m_DiscardPile(std::make_shared<CardPile>(748.0f, 50.0f)),
    m_ViewDeck(std::make_unique<Button>(500.0f, 570.0f, 50, 50, "viewDeckButton")),
    m_HealthText(std::make_unique<Text>(std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 660.0f, 575.0f, 10.0f, 0.0f)),
    m_EnergyText(std::make_unique<Text>(std::to_string(m_Energy), 740.0f, 575.0f, 10.0f, 0.0f)),
    m_WoodText(std::make_unique<Text>(std::to_string(m_Resources.w), 50.0f, 575.0f, 10.0f, 0.0f)),
    m_StoneText(std::make_unique<Text>(std::to_string(m_Resources.x), 125.0f, 575.0f, 10.0f, 0.0f)),
    m_WheatText(std::make_unique<Text>(std::to_string(m_Resources.y), 200.0f, 575.0f, 10.0f, 0.0f)),
    m_GoldText(std::make_unique<Text>(std::to_string(m_Resources.z), 275.0f, 575.0f, 10.0f, 0.0f)),
    m_DayText(std::make_unique<Text>("Day: " + std::to_string(GetDay()), 400.0f, 575.0f, 10.0f, 0.0f)),
    m_HealthIcon(std::make_unique<Image>("healthIcon", 620.0f, 575.0f, 20, 20, 0.0f)),
    m_EnergyIcon(std::make_unique<Image>("energyIcon", 710.0f, 575.0f, 20, 20, 0.0f)),
    m_WoodIcon(std::make_unique<Image>("woodIcon", 80.0f, 575.0f, 20, 20, 0.0f)),
    m_StoneIcon(std::make_unique<Image>("stoneIcon", 155.0f, 575.0f, 20, 20, 0.0f)),
    m_WheatIcon(std::make_unique<Image>("wheatIcon", 230.0f, 575.0f, 20, 20, 0.0f)),
    m_GoldIcon(std::make_unique<Image>("goldIcon", 305.0f, 575.0f, 20, 20, 0.0f)),
    m_Artifacts(std::make_shared<ArtifactPile>(570.0f, 570.0f))
{
    m_HealthText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_EnergyText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_WoodText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_StoneText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_WheatText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_GoldText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_DayText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_TextColor = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

    //Set Draw and discard piles to be shown in random orders
    m_DrawPile->SetOrdered(false);
    m_DiscardPile->SetOrdered(false);
    m_Deck->SetOrdered(true);
}

TowerDefense::Player& TowerDefense::Player::Get()
{
    static Player instance;
    return instance;
}

void TowerDefense::Player::Reset()
{
    SetHealth(100);
    SetMaxHealth(100);
    SetEnergy(100);
    SetResource(0, Resource::WOOD);
    SetResource(0, Resource::STONE);
    SetResource(0, Resource::WHEAT);
    SetResource(0, Resource::GOLD);
    m_Hand = std::make_shared<Hand>(10);
    m_Deck = std::make_shared<CardPile>(-100.0f, 0.0f);
    m_DrawPile = std::make_shared<CardPile>(49.0f, 50.0f);
    m_DiscardPile = std::make_shared<CardPile>(748.0f, 50.0f);
    m_Artifacts = std::make_shared<ArtifactPile>(570.0f, 570.0f);

    //Starter Deck
    for (int i = 0; i < 8; i++)
        AddToDeck(std::make_shared<Focus>(false));
    for (int i = 0; i < 4; i++)
        AddToDeck(std::make_shared<ArcherCard>());
    for (int i = 0; i < 2; i++)
        AddToDeck(std::make_shared<PotOfGreed>());
}

void TowerDefense::Player::SetEnergy(int energy)
{
    m_Energy = energy;
    m_EnergyText = std::make_unique<Text>(std::to_string(m_Energy), 740.0f, 575.0f, 10.0f, 0.0f);
    m_EnergyText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::ChangeEnergy(int change)
{
    m_Energy += change;
    if (m_Energy > 9999)
        m_Energy = 9999;
    m_EnergyText = std::make_unique<Text>(std::to_string(m_Energy), 740.0f, 575.0f, 10.0f, 0.0f);
    m_EnergyText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

int TowerDefense::Player::GetResource(Resource res) const
{
    if (res == Resource::WOOD)
        return m_Resources.w;
    else if (res == Resource::STONE)
        return m_Resources.x;
    else if (res == Resource::WHEAT)
        return m_Resources.y;
    else if (res == Resource::GOLD)
        return m_Resources.z;
    else
        return -1;
}

void TowerDefense::Player::SetResource(int total, Resource res)
{
    if (res == Resource::WOOD)
    {
        m_Resources.w = total;
        m_WoodText = std::make_unique<Text>(std::to_string(m_Resources.w), 50.0f, 575.0f, 10.0f, 0.0f);
        m_WoodText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }   
    else if (res == Resource::STONE)
    {
        m_Resources.x = total;
        m_StoneText = std::make_unique<Text>(std::to_string(m_Resources.x), 125.0f, 575.0f, 10.0f, 0.0f);
        m_StoneText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    } 
    else if (res == Resource::WHEAT)
    {
        m_Resources.y = total;
        m_WheatText = std::make_unique<Text>(std::to_string(m_Resources.y), 200.0f, 575.0f, 10.0f, 0.0f);
        m_WheatText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if (res == Resource::GOLD)
    {
        m_Resources.z = total;
        m_GoldText = std::make_unique<Text>(std::to_string(m_Resources.z), 275.0f, 575.0f, 10.0f, 0.0f);
        m_GoldText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }    
}

void TowerDefense::Player::ChangeResource(int change, Resource res)
{
    if (res == Resource::WOOD)
    {
        m_Resources.w += change;
        m_WoodText = std::make_unique<Text>(std::to_string(m_Resources.w), 50.0f, 575.0f, 10.0f, 0.0f);
        m_WoodText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if (res == Resource::STONE)
    {
        m_Resources.x += change;
        m_StoneText = std::make_unique<Text>(std::to_string(m_Resources.x), 125.0f, 575.0f, 10.0f, 0.0f);
        m_StoneText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if (res == Resource::WHEAT)
    {
        m_Resources.y += change;
        m_WheatText = std::make_unique<Text>(std::to_string(m_Resources.y), 200.0f, 575.0f, 10.0f, 0.0f);
        m_WheatText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if (res == Resource::GOLD)
    {
        m_Resources.z += change;
        m_GoldText = std::make_unique<Text>(std::to_string(m_Resources.z), 275.0f, 575.0f, 10.0f, 0.0f);
        m_GoldText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

void TowerDefense::Player::SetHealth(int health)
{
    m_Health = health;
    m_HealthText = std::make_unique<Text>(std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 660.0f, 575.0f, 10.0f, 0.0f);
    m_HealthText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::ChangeHealth(int change)
{
    m_Health += change;
    if (m_Health < 1)
    {
        m_Health = 0;
        TowerDefense::SetScene(SceneType::POSTCOMBAT);
    }
    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
    m_HealthText = std::make_unique<Text>(std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 660.0f, 575.0f, 10.0f, 0.0f);
    m_HealthText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::SetMaxHealth(int health)
{
    m_MaxHealth = health;
    m_HealthText = std::make_unique<Text>(std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 660.0f, 575.0f, 10.0f, 0.0f);
    m_HealthText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::ChangeMaxHealth(int change)
{
    m_MaxHealth += change; 
    if (m_Health > m_MaxHealth) 
        m_Health = m_MaxHealth;
    m_HealthText = std::make_unique<Text>(std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 660.0f, 575.0f, 10.0f, 0.0f);
    m_HealthText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::RenderStats()
{
    m_HealthIcon->Render(); 
    m_HealthText->Render();
    m_EnergyIcon->Render(); 
    m_EnergyText->Render();
    m_WoodIcon->Render();
    m_StoneIcon->Render();
    m_WheatIcon->Render();
    m_GoldIcon->Render(); 
    m_WoodText->Render();
    m_StoneText->Render();
    m_WheatText->Render();
    m_GoldText->Render();
    m_DayText->Render();
}

void TowerDefense::Player::RenderDeckAndArtifacts()
{
    m_ViewDeck->Render();
    m_Artifacts->Render();

    if (DeckShowing())
    {
        m_Deck->RenderCards();
        if (!GetSelectedDeckCard())
            m_ViewDeck->Render();
    }
    else if (ArtifactsShowing())
    {
        m_Artifacts->RenderArtifacts();
        if (!GetSelectedArtifact())
            m_Artifacts->Render();
    }
}

void TowerDefense::Player::UpdateDeckAndArtifacts()
{
    if (!GetSelectedDeckCard() && !ArtifactsShowing())
    {
        m_ViewDeck->Update();
        if (m_ViewDeck->IsClicked())
            m_Deck->Show(!m_Deck->IsShowing());
    }

    if (DeckShowing())
        m_Deck->Update();
    else
        m_Artifacts->Update();
}

void TowerDefense::Player::UpdateDayText()
{
    m_DayText = std::make_unique<Text>(std::string("Day: ") + std::to_string(GetDay()), 400.0f, 575.0f, 10.0f, 0.0f);
    m_DayText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::SetTextColor(float r, float g, float b, float a)
{
    m_HealthText->SetColor(r, g, b, a);
    m_EnergyText->SetColor(r, g, b, a);
    m_WoodText->SetColor(r, g, b, a);
    m_StoneText->SetColor(r, g, b, a);
    m_WheatText->SetColor(r, g, b, a);
    m_GoldText->SetColor(r, g, b, a);
    m_DayText->SetColor(r, g, b, a);
    m_TextColor = Vec4(r, g, b, a);
}

void TowerDefense::Player::DrawHand()
{
    m_Hand->DiscardHand();

    for (int i = 0; i < 5; i++) {
        m_Hand->DrawCard();
    }
}

void TowerDefense::Player::ResetCardPiles()
{
    m_Hand->DiscardHand();
    m_DiscardPile->Clear();
    m_Deck->Copy(m_DrawPile);
    m_DrawPile->Shuffle();
    DrawHand();
}

//Called at end of program to clean up memory
//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
void TowerDefense::Player::CleanUp()
{
    m_Hand.reset();
    m_DiscardPile.reset();
    m_DrawPile.reset();
    m_Deck.reset();
    m_ViewDeck.reset();
    m_HealthText.reset();
    m_EnergyText.reset();
    m_WoodText.reset();
    m_StoneText.reset();
    m_WheatText.reset();
    m_GoldText.reset();
    m_DayText.reset();
    m_Artifacts.reset();
    m_HealthIcon.reset();
    m_EnergyIcon.reset();
    m_WoodIcon.reset();
    m_StoneIcon.reset();
    m_WheatIcon.reset();
    m_GoldIcon.reset();
}

void TowerDefense::Player::AddToDeck(std::shared_ptr<Card> c)
{
    m_Deck->AddCard(c);
    ArtifactOnAddCard(c);
}

void TowerDefense::Player::RemoveFromDeck(int index)
{
    m_Deck->RemoveCard(index);
}

int TowerDefense::Player::GetCardIndex(std::shared_ptr<Card> c)
{
    for (int i = 0; i < (int)m_Deck->GetSize(); i++)
    {
        if (m_Deck->GetCard(i) == c)
        {
            return i;
        }
    }
    return -1;
}


void TowerDefense::Player::AddToArtifacts(std::shared_ptr<Artifact> a)
{
    m_Artifacts->AddArtifact(a);
    a->OnAquire();
}

void TowerDefense::Player::RemoveFromArtifacts(int index)
{
    m_Artifacts->RemoveArtifact(index);
}

void TowerDefense::Player::ArtifactOnAddCard(std::shared_ptr<Card> c)
{
    for (int i = 0; i < m_Artifacts->GetSize(); i++)
        m_Artifacts->GetArtifact(i)->OnAddCard(c);
}

void TowerDefense::Player::ArtifactOnRoundStart()
{
    for (int i = 0; i < m_Artifacts->GetSize(); i++)
        m_Artifacts->GetArtifact(i)->OnRoundStart();
}

void TowerDefense::Player::ArtifactOnCardPlay(std::shared_ptr<Card> c)
{
    for (int i = 0; i < m_Artifacts->GetSize(); i++)
        m_Artifacts->GetArtifact(i)->OnCardPlay(c);
}

void TowerDefense::Player::ArtifactOnFightStart()
{
    for (int i = 0; i < m_Artifacts->GetSize(); i++)
        m_Artifacts->GetArtifact(i)->OnFightStart();
}

void TowerDefense::Player::ArtifactOnFightEnd()
{
    for (int i = 0; i < m_Artifacts->GetSize(); i++)
        m_Artifacts->GetArtifact(i)->OnFightEnd();
}