#pragma once
#include "core/Button.h"

namespace TowerDefense
{
	class SkillTreeSkill : public Button, public std::enable_shared_from_this<SkillTreeSkill>
	{
	public:
		SkillTreeSkill(const std::string& image, const std::string& name, std::shared_ptr<SkillTreeSkill> parent);

		void Update() override;

		void Render() override;

		void RenderInfo() const;

		virtual void Apply() = 0;

		void SetPosition(float x, float y, float treeWidth);

		inline std::shared_ptr<SkillTreeSkill> GetParent() const { return m_Parent; }
		inline std::vector<std::shared_ptr<SkillTreeSkill>> GetChildren() const { return m_Children; }

		void AddChild(std::shared_ptr<SkillTreeSkill> child);

		std::shared_ptr<const SkillTreeSkill> GetSelectedSkill() const;

		inline bool IsApplied() const { return m_Applied; }

		inline const std::string& GetName() const { return m_Name; }

		void SetRequirementText(const std::string& text);

		const std::string GetSkillsSelected() const;
		void SetSkillsSelected(const std::string& selected);

		int GetNumInTree() const;

		int GetNumApplied() const;

	private:
		bool m_Applied;
		std::string m_Name;

		std::unique_ptr<Image> m_InfoImage;
		std::unique_ptr<Text> m_NameText, m_RequirementText;

		std::shared_ptr<SkillTreeSkill> m_Parent;
		std::vector<std::shared_ptr<SkillTreeSkill>> m_Children;
		std::vector<std::shared_ptr<Line>> m_Lines;

	protected:
		std::unique_ptr<Text> m_InfoText;

	};

	class ArcherDamage : public SkillTreeSkill
	{
	public:
		ArcherDamage(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class MultiShot : public SkillTreeSkill
	{
	public:
		MultiShot(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class ArcherCritChance : public SkillTreeSkill
	{
	public:
		ArcherCritChance(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class ArcherCritDamage : public SkillTreeSkill
	{
	public:
		ArcherCritDamage(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class WizardDamage : public SkillTreeSkill
	{
	public:
		WizardDamage(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class ScholarFocus : public SkillTreeSkill
	{
	public:
		ScholarFocus(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class HolyPower : public SkillTreeSkill
	{
	public:
		HolyPower(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class MusicPower : public SkillTreeSkill
	{
	public:
		MusicPower(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class AlchemistDamage : public SkillTreeSkill
	{
	public:
		AlchemistDamage(int level, std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class ArcherLevel10 : public SkillTreeSkill
	{
	public:
		ArcherLevel10(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class WizardLevel10 : public SkillTreeSkill
	{
	public:
		WizardLevel10(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class TempleLevel10 : public SkillTreeSkill
	{
	public:
		TempleLevel10(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class MusicHallLevel10 : public SkillTreeSkill
	{
	public:
		MusicHallLevel10(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};

	class AlchemyLabLevel10 : public SkillTreeSkill
	{
	public:
		AlchemyLabLevel10(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};
}
