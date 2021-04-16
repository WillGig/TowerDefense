#include "pch.h"
#include "Player.h"
#include "cards/Focus.h"
#include "TowerDefense.h"

TowerDefense::Player::Player()
    :m_Health(100), m_MaxHealth(100), m_Energy(100), m_Hand(std::make_shared<Hand>(10)),
    m_Deck(std::make_shared<CardPile>(-100.0f,0.0f)), 
    m_DrawPile(std::make_shared<CardPile>(49.0f, 50.0f)),
    m_DiscardPile(std::make_shared<CardPile>(748.0f, 50.0f))
{
}

TowerDefense::Player& TowerDefense::Player::Get()
{
    static Player instance;
    return instance;
}

void TowerDefense::Player::ChangeEnergy(int change)
{
    m_Energy += change;
}

void TowerDefense::Player::ChangeHealth(int change)
{
    m_Health += change;
    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
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
}