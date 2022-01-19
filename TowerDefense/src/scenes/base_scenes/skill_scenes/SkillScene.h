#pragma once
#include "scenes/base_scenes/BaseScene.h"
#include "skill_trees/SkillTreeSkill.h"

namespace TowerDefense
{
	class SkillScene : public BaseScene
	{
	public:
		SkillScene(const std::string& button, const std::string& description, int coolDown);
		void Render() override;
		void Update() override;

		inline const std::string GetSkillsSelected() const { return m_Tree->GetSkillsSelected(); }
		inline void SetSkillsSelected(const std::string& selected) { m_Tree->SetSkillsSelected(selected); }

	protected:
		std::shared_ptr<SkillTreeSkill> m_Tree;

	private:
		std::unique_ptr<Button> m_BackToCamp;
	};

	class ArcheryRange : public SkillScene
	{
	public:
		ArcheryRange();
		inline std::string GetName() override { return "ArcheryRange"; }
	};

	class WizardTower : public SkillScene
	{
	public:
		WizardTower();
		inline std::string GetName() override { return "WizardTower"; }
	};

	class Temple : public SkillScene
	{
	public:
		Temple();
		inline std::string GetName() override { return "Temple"; }
	};

	class AlchemyLab : public SkillScene
	{
	public:
		AlchemyLab();
		inline std::string GetName() override { return "AlchemyLab"; }
	};

	class MusicHall : public SkillScene
	{
	public:
		MusicHall();
		inline std::string GetName() override { return "MusicHall"; }
	};
}