#include "pch.h"
#include "LightningBolt.h"
#include "scenes/Combat.h"

TowerDefense::LightningBolt::LightningBolt(Vec2 start, Vec2 end)
	:Entity((start.x + end.x) / 2.0f, (start.y + end.y) / 2.0f, (int)abs(start.x-end.x), (int)abs(start.y-end.y), 0.0f, "", Type::ANIMATION),
	m_Bolt(std::make_unique<Line>(GenerateBolt(start, end)))
{
}

void TowerDefense::LightningBolt::Render()
{
	m_Bolt->Render();
}

void TowerDefense::LightningBolt::Update()
{
	Vec4 c = m_Bolt->GetColor();
    m_Bolt->SetColor(c.w, c.x, c.y, c.z - .05f);

	if (c.z < .1f)
		Combat::RemoveEntity(GetID());
}

std::vector<Vec2> TowerDefense::LightningBolt::GenerateBolt(Vec2 start, Vec2 end)
{
    float length = sqrt(pow(start.x - end.x, 2.0f) + pow(start.y - end.y, 2.0f));

    std::vector<Vec2> results;
    Vec2 tangent = end - start;
    Vec2 normal(tangent.y / length, -tangent.x / length);
   

    std::vector<float> positions;
    positions.push_back(0);

    for (int i = 0; i < length / 4; i++)
        positions.push_back(Random::GetFloat());

    std::sort(positions.begin(), positions.end());

    const float Sway = 80;
    const float Jaggedness = 1 / Sway;

    Vec2 prev =  start;
    float prevDisplacement = 0;
    for (int i = 1; i < (int)positions.size(); i++)
    {
        float pos = positions[i];

        // used to prevent sharp angles by ensuring very close positions also have small perpendicular variation.
        float scale = (length * Jaggedness) * (pos - positions[i - 1]);

        // defines an envelope. Points near the middle of the bolt can be further from the central line.
        float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

        float displacement = Random::GetFloat() * Sway * 2 - Sway;
        displacement -= (displacement - prevDisplacement) * (1 - scale);
        displacement *= envelope;

        Vec2 point = start + tangent*pos + normal * displacement;
        //results.push_back(Line(prev, point));
        results.push_back(prev);
        results.push_back(point);
        prev = point;
        prevDisplacement = displacement;
    }

    //results.push_back(Line(prev, end));
    results.push_back(prev);
    results.push_back(end);

    return results;
}