#include "pch.h"
#include "Aura.h"
#include "scenes/Combat.h"

TowerDefense::Aura::ConstantDamage::ConstantDamage(float damage, int time)
	:Aura("constantDamage", "Deal " + Utils::TruncateFloat(damage, 1) + " Damage every " + Utils::TruncateFloat((float)time/60.0f, 1) + "\nSeconds to All Enemies"),
	m_Damage(damage), m_Time(time), m_NextDamage(0)
{
}

void TowerDefense::Aura::ConstantDamage::Update()
{
	Aura::Update();

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_NextDamage == 0)
		{
			auto entities = Combat::GetEntities();
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				auto e = entities->at(i);
				if (e->GetEntityType() == Type::ENEMY)
				{
					std::dynamic_pointer_cast<Enemy::Enemy>(e)->TakeDamage(m_Damage, GetID(), Tower::DamageType::MAGIC);
					m_NextDamage = m_Time;
				}
			}
		}
		else
			m_NextDamage--;
	}
}

void TowerDefense::Aura::ConstantDamage::Combine(std::shared_ptr<Aura> other)
{
	auto otherConstantDamage = std::dynamic_pointer_cast<ConstantDamage>(other);
	if (otherConstantDamage)
	{
		m_Damage += otherConstantDamage->GetDamage();
		m_InfoText = std::make_unique<Text>("Deal " + Utils::TruncateFloat(m_Damage, 1) + " Damage every " + Utils::TruncateFloat((float)m_Time / 60.0f, 1) + "\nSeconds to All Enemies", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
		
}

const std::string TowerDefense::Aura::ConstantDamage::GetSaveData() const
{
	return "Constant Damage\n" + Utils::TruncateFloat(m_Damage, 1);
}