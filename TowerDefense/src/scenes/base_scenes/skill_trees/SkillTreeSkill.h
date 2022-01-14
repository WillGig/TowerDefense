#pragma once
#include "core/Button.h"

namespace TowerDefense
{
	class SkillTreeSkill : public Button, public std::enable_shared_from_this<SkillTreeSkill>
	{
	public:
		SkillTreeSkill(const std::string& image, const std::string& name, int cost, std::shared_ptr<SkillTreeSkill> parent);

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

		inline int GetCost() const { return m_Cost; }

		bool HasCost() const;

		void SetRequirementText(const std::string& text);

	private:
		bool m_Applied;
		int m_Cost;
		std::string m_Name;

		std::unique_ptr<Image> m_InfoImage;
		std::unique_ptr<Text> m_RequirementText;

		std::shared_ptr<SkillTreeSkill> m_Parent;
		std::vector<std::shared_ptr<SkillTreeSkill>> m_Children;
		std::vector<std::shared_ptr<Line>> m_Lines;

	protected:
		std::unique_ptr<Text> m_InfoText;

	};

	class TestSkill : public SkillTreeSkill
	{
	public:
		TestSkill();
		TestSkill(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};
}
