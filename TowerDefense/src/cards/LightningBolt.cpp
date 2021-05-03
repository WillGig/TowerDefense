#include "pch.h"
#include "LightningBolt.h"
#include "scenes/Combat.h"

TowerDefense::LightningBolt::LightningBolt(float startX, float startY, float endX, float endY)
	:Entity((startX + endX) / 2.0f, (startY + endY) / 2.0f, (int)abs(startX-endX), (int)abs(startY-endY), 0.0f, "", Type::ANIMATION),
	m_Bolt(std::make_unique<std::vector<Line>>(GenerateBolt(startX, startY, endX, endY)))
{
}

void TowerDefense::LightningBolt::Render()
{
	for (int i = 0; i < (int)m_Bolt->size(); i++)
		m_Bolt->at(i).Render();
}

void TowerDefense::LightningBolt::Update()
{
	Vec4 c = m_Bolt->at(0).GetColor();
	for (int i = 0; i < (int)m_Bolt->size(); i++)
	{
		m_Bolt->at(i).SetColor(c.w, c.x, c.y, c.z * .98f);
	}

	if (c.z < .1f)
		Combat::RemoveEntity(GetID());
}

std::vector<Line> TowerDefense::LightningBolt::GenerateBolt(float startX, float startY, float endX, float endY)
{
    float length = sqrt(pow(startX - endX, 2.0f) + pow(startY - endY, 2.0f));

    std::vector<Line> results;
    float tangentX = endX - startX;
    float tangentY = endY - startY;
    float normalX = tangentY / length;
    float normalY = -tangentX / length;
   

    std::vector<float> positions;
    positions.push_back(0);

    for (int i = 0; i < length / 4; i++)
        positions.push_back(Random::GetFloat());

    std::sort(positions.begin(), positions.end());

    const float Sway = 80;
    const float Jaggedness = 1 / Sway;

    float prevX = startX;
    float prevY = startY;
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

        float pointX = startX + pos * tangentX + displacement * normalX;
        float pointY = startY + pos * tangentY + displacement * normalY;

        results.push_back(Line(prevX, prevY, pointX, pointY));
        prevX = pointX;
        prevY = pointY;
        prevDisplacement = displacement;
    }

    results.push_back(Line(prevX, prevY, endX, endY));

    return results;
}