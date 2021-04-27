#include "pch.h"
#include "Player.h"
#include "cards/Focus.h"

TowerDefense::Player::Player()
    :m_Health(100), m_MaxHealth(100), m_Energy(100), m_Hand(std::make_shared<Hand>(10)),
    m_Deck(std::make_shared<CardPile>(-100.0f,0.0f)), 
    m_DrawPile(std::make_shared<CardPile>(49.0f, 50.0f)),
    m_DiscardPile(std::make_shared<CardPile>(748.0f, 50.0f)),
    m_ViewDeck(std::make_unique<Button>(570.0f, 578.0f, 50, 43, "viewDeckButton")),
    m_HealthText(std::make_unique<Text>(std::string("HP: ") + std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 645.0f, 575.0f, 10.0f, 0.0f)),
    m_EnergyText(std::make_unique<Text>(std::string("Energy: ") + std::to_string(m_Energy), 740.0f, 575.0f, 10.0f, 0.0f)),
    m_DayText(std::make_unique<Text>(std::string("Day: ") + std::to_string(GetDay()), 400.0f, 575.0f, 10.0f, 0.0f)),
    m_Artifacts(std::make_unique<std::vector<std::shared_ptr<Artifact>>>())
{
    m_HealthText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_EnergyText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
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

void TowerDefense::Player::ChangeEnergy(int change)
{
    m_Energy += change;
    m_EnergyText = std::make_unique<Text>(std::string("Energy: ") + std::to_string(m_Energy), 740.0f, 575.0f, 10.0f, 0.0f);
    m_EnergyText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::ChangeHealth(int change)
{
    m_Health += change;
    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
    m_HealthText = std::make_unique<Text>(std::string("HP: ") + std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 645.0f, 575.0f, 10.0f, 0.0f);
    m_HealthText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
}

void TowerDefense::Player::ChangeMaxHealth(int change)
{
    m_MaxHealth += change; 
    if (m_Health > m_MaxHealth) 
        m_Health = m_MaxHealth;
    m_HealthText = std::make_unique<Text>(std::string("HP: ") + std::to_string(m_Health) + "/" + std::to_string(m_MaxHealth), 645.0f, 575.0f, 10.0f, 0.0f);
    m_HealthText->SetColor(m_TextColor.w, m_TextColor.x, m_TextColor.y, m_TextColor.z);
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
    m_DayText.reset();
    m_Artifacts.reset();
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

void TowerDefense::Player::AddArtifact(std::shared_ptr<Artifact> a)
{
    m_Artifacts->push_back(a);
    a->OnAquire();
}

void TowerDefense::Player::ArtifactOnAddCard(std::shared_ptr<Card> c)
{
    for (unsigned int i = 0; i < m_Artifacts->size(); i++)
        m_Artifacts->at(i)->OnAddCard(c);
}

void TowerDefense::Player::ArtifactOnRoundStart()
{
    for (unsigned int i = 0; i < m_Artifacts->size(); i++)
        m_Artifacts->at(i)->OnRoundStart();
}

void TowerDefense::Player::ArtifactOnCardPlay(std::shared_ptr<Card> c)
{
    for (unsigned int i = 0; i < m_Artifacts->size(); i++)
        m_Artifacts->at(i)->OnCardPlay(c);
}

void TowerDefense::Player::ArtifactOnFightStart()
{
    for (unsigned int i = 0; i < m_Artifacts->size(); i++)
        m_Artifacts->at(i)->OnFightStart();
}

void TowerDefense::Player::ArtifactOnFightEnd()
{
    for (unsigned int i = 0; i < m_Artifacts->size(); i++)
        m_Artifacts->at(i)->OnFightEnd();
}