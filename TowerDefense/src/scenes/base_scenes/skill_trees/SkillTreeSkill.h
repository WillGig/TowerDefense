#pragma once
#include "core/Button.h"

namespace TowerDefense
{
	class SkillTreeSkill : public Button
	{
	public:
		SkillTreeSkill(const std::string& image, std::shared_ptr<SkillTreeSkill> parent);

		void Update() override;

		void Render() override;

		virtual void Apply() = 0;

		void SetPosition(float x, float y, float treeWidth);

		inline std::shared_ptr<SkillTreeSkill> GetParent() const { return m_Parent; }
		inline std::vector<std::shared_ptr<SkillTreeSkill>> GetChildren() const { return m_Children; }

		void AddChild(std::shared_ptr<SkillTreeSkill> child);

		inline bool IsApplied() const { return m_Applied; }

	private:
		bool m_Applied;

		std::shared_ptr<SkillTreeSkill> m_Parent;
		std::vector<std::shared_ptr<SkillTreeSkill>> m_Children;
		std::vector<std::shared_ptr<Line>> m_Lines;
	};

	class TestSkill : public SkillTreeSkill
	{
	public:
		TestSkill();
		TestSkill(std::shared_ptr<SkillTreeSkill> parent);
		void Apply() override;
	};
}
