#include "pch.h"
#include "TowerDefense.h"

Text::Text(std::string msg, float x, float y, float size, float maxWidth)
	:m_Message(msg), m_Position(x, y, 0.0f), m_Color(0.0f, 0.0f, 0.0f, 1.0f), m_Width(0)
{
	float scale = size / 12.0f;

	//setting vertex and index buffer data sizes based on number of characters
	std::unique_ptr<float[]> positions = std::make_unique<float[]>(msg.length() * 16);
	std::unique_ptr<unsigned int[]> indices = std::make_unique<unsigned int[]>(msg.length() * 6);

	//positions of a single character that will be added to the vertex buffer data
	std::unique_ptr<float[]> tempPositions;

	int longestLine = 0;

	//Offset of current character
	int xOffSet = 0;
	int yOffSet = 0;
	for (unsigned int i = 0; i < msg.length(); i++)
	{

		if (msg[i] == ' ')
		{
			xOffSet += 6;
			m_Width += 6;
			continue;
		}
		else if (msg[i] == '\n' || (maxWidth > 0 && xOffSet + GetWidth(msg[i]) > maxWidth))
		{
			if (msg[i] == '\n') {
				longestLine = (int)(maxWidth > longestLine ? maxWidth : longestLine);
			}
			else {
				longestLine = (int)(maxWidth*scale);
			}

			yOffSet -= (int)(20 * scale);
			xOffSet = 0;
			m_Width = 0;
			continue;
		}

		//Get vertex data for current character
		tempPositions = GetPositions(msg[i], xOffSet, yOffSet, scale);
		for (int j = 0; j < 16; j++)
		{
			positions[i * 16 + j] = tempPositions[j];
		}

		//Add indicies for the character to the index buffer
		for (int j = 0; j < 6; j++)
		{
			if (j < 3)
				indices[j + i * 6] = j + i * 4;
			else
				indices[j + i * 6] = (j - 1) % 4 + i * 4;
		}

		//Update offset based on the width of the current character and the following one
		if (i != msg.length() - 1)
			xOffSet += (int)((GetWidth(msg[i]) / 2 + GetWidth(msg[i + 1]) / 2 + 2));

		m_Width += (int)(GetWidth(msg[i]) * scale);
	}

	if (longestLine > m_Width)
		m_Width = longestLine;

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(&positions[0], msg.length() * 16 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], msg.length() * 6);

	m_Shader = std::make_unique<Shader>("res/shaders/Text.Shader");
	m_Shader->Bind();
	m_Texture = std::make_unique<Texture>("res/textures/highResFont.png");
	m_Shader->SetUniform1i("u_Texture", 0);
}

void Text::Render()
{
	m_Texture->Bind();
	{
		Mat4f mvp = Renderer::Get().GetProjectionMatrix() * Mat4f::Translate(m_Position);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform4f("u_Color", m_Color.w, m_Color.x, m_Color.y, m_Color.z);
		Renderer::Get().Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}
}

void Text::SetColor(float r, float g, float b, float a)
{
	m_Color.w = r;
	m_Color.x = g;
	m_Color.y = b;
	m_Color.z = a;
}

//Gets vertex positions for given char from the fontsheet. 
std::unique_ptr<float[]> Text::GetPositions(char c, int xOff, int yOff, float scale)
{
	float width = GetWidth(c);
	float height = 16;
	auto coords = GetCoords(c);

	std::unique_ptr<float[]> pos = std::make_unique<float[]>(16);

	pos[0] = (-width / 2 + xOff) * scale;
	pos[1] = (-height / 2 + yOff) * scale;
	pos[2] = ((coords.first - width / 2) / 208.0f);
	pos[3] = ((coords.second - height / 2) / 96.0f);
	pos[4] = (width / 2 + xOff) * scale;
	pos[5] = (-height / 2 + yOff) * scale;
	pos[6] = ((coords.first + width / 2) / 208.0f);
	pos[7] = ((coords.second - height / 2) / 96.0f);
	pos[8] = (width / 2 + xOff) * scale;
	pos[9] = (height / 2 + yOff) * scale;
	pos[10] = ((coords.first + width / 2) / 208.0f);
	pos[11] = ((coords.second + height / 2) / 96.0f);
	pos[12] = (-width / 2 + xOff) * scale;
	pos[13] = (height / 2 + yOff) * scale;
	pos[14] = ((coords.first - width / 2) / 208.0f);
	pos[15] = ((coords.second + height / 2) / 96.0f);

	return pos;
}

//Hardcoded values of character widths relative to font sheet scale
float Text::GetWidth(char c) const
{
	switch (c)
	{
	case '0': return 8.0f;
	case '1': return 6.0f;
	case '2': return 8.0f;
	case '3': return 8.0f;
	case '4': return 8.0f;
	case '5': return 8.0f;
	case '6': return 8.0f;
	case '7': return 8.0f;
	case '8': return 8.0f;
	case '9': return 8.0f;
	case '.': return 2.0f;
	case ',': return 2.0f;
	case '!': return 2.0f;
	case ' ': return 8.0f;
	case '\n': return 0.0f;
	case 'a': return 8.0f;
	case 'b': return 8.0f;
	case 'c': return 8.0f;
	case 'd': return 8.0f;
	case 'e': return 8.0f;
	case 'f': return 6.0f;
	case 'g': return 8.0f;
	case 'h': return 8.0f;
	case 'i': return 2.0f;
	case 'j': return 4.0f;
	case 'k': return 8.0f;
	case 'l': return 2.0f;
	case 'm': return 12.0f;
	case 'n': return 8.0f;
	case 'o': return 8.0f;
	case 'p': return 8.0f;
	case 'q': return 8.0f;
	case 'r': return 6.0f;
	case 's': return 8.0f;
	case 't': return 6.0f;
	case 'u': return 8.0f;
	case 'v': return 8.0f;
	case 'w': return 14.0f;
	case 'x': return 8.0f;
	case 'y': return 10.0f;
	case 'z': return 8.0f;
	case 'A': return 12.0f;
	case 'B': return 10.0f;
	case 'C': return 10.0f;
	case 'D': return 10.0f;
	case 'E': return 10.0f;
	case 'F': return 8.0f;
	case 'G': return 10.0f;
	case 'H': return 10.0f;
	case 'I': return 2.0f;
	case 'J': return 8.0f;
	case 'K': return 10.0f;
	case 'L': return 8.0f;
	case 'M': return 12.0f;
	case 'N': return 10.0f;
	case 'O': return 10.0f;
	case 'P': return 10.0f;
	case 'Q': return 10.0f;
	case 'R': return 12.0f;
	case 'S': return 10.0f;
	case 'T': return 10.0f;
	case 'U': return 10.0f;
	case 'V': return 12.0f;
	case 'W': return 16.0f;
	case 'X': return 10.0f;
	case 'Y': return 10.0f;
	case 'Z': return 10.0f;
	case '?': return 8.0f;
	case '\'': return 2.0f;
	case '*': return 6.0f;
	case '#': return 8.0f;
	case '"': return 4.0f;
	case '%': return 16.0f;
	case ':': return 2.0f;
	case '(': return 4.0f;
	case ')': return 4.0f;
	case '/': return 4.0f;
	case '-': return 4.0f;
	case '+': return 8.0f;
	case '=': return 8.0f;
	}

	std::cout << "Error Char " << c << " not found!" << std::endl;
	return -1;
}

//Hardcoded coords of character in font sheet
std::pair<float, float> Text::GetCoords(char c)
{
	switch (c)
	{
	case '0': return std::make_pair<float, float>(4.0f, 24.0f);
	case '1': return std::make_pair<float, float>(19.0f, 24.0f);
	case '2': return std::make_pair<float, float>(36.0f, 24.0f);
	case '3': return std::make_pair<float, float>(52.0f, 24.0f);
	case '4': return std::make_pair<float, float>(68.0f, 24.0f);
	case '5': return std::make_pair<float, float>(84.0f, 24.0f);
	case '6': return std::make_pair<float, float>(100.0f, 24.0f);
	case '7': return std::make_pair<float, float>(116.0f, 24.0f);
	case '8': return std::make_pair<float, float>(132.0f, 24.0f);
	case '9': return std::make_pair<float, float>(148.0f, 24.0f);
	case '.': return std::make_pair<float, float>(161.0f, 24.0f);
	case ',': return std::make_pair<float, float>(177.0f, 24.0f);
	case '!': return std::make_pair<float, float>(193.0f, 24.0f);
	case 'a': return std::make_pair<float, float>(4.0f, 88.0f);
	case 'b': return std::make_pair<float, float>(20.0f, 88.0f);
	case 'c': return std::make_pair<float, float>(36.0f, 88.0f);
	case 'd': return std::make_pair<float, float>(52.0f, 88.0f);
	case 'e': return std::make_pair<float, float>(68.0f, 88.0f);
	case 'f': return std::make_pair<float, float>(83.0f, 88.0f);
	case 'g': return std::make_pair<float, float>(100.0f, 89.0f);
	case 'h': return std::make_pair<float, float>(116.0f, 88.0f);
	case 'i': return std::make_pair<float, float>(129.0f, 88.0f);
	case 'j': return std::make_pair<float, float>(146.0f, 89.0f);
	case 'k': return std::make_pair<float, float>(164.0f, 88.0f);
	case 'l': return std::make_pair<float, float>(177.0f, 88.0f);
	case 'm': return std::make_pair<float, float>(198.0f, 88.0f);
	case 'n': return std::make_pair<float, float>(4.0f, 72.0f);
	case 'o': return std::make_pair<float, float>(20.0f, 72.0f);
	case 'p': return std::make_pair<float, float>(36.0f, 72.0f);
	case 'q': return std::make_pair<float, float>(52.0f, 72.0f);
	case 'r': return std::make_pair<float, float>(67.0f, 72.0f);
	case 's': return std::make_pair<float, float>(84.0f, 72.0f);
	case 't': return std::make_pair<float, float>(99.0f, 72.0f);
	case 'u': return std::make_pair<float, float>(116.0f, 72.0f);
	case 'v': return std::make_pair<float, float>(132.0f, 72.0f);
	case 'w': return std::make_pair<float, float>(151.0f, 72.0f);
	case 'x': return std::make_pair<float, float>(164.0f, 72.0f);
	case 'y': return std::make_pair<float, float>(181.0f, 72.0f);
	case 'z': return std::make_pair<float, float>(196.0f, 72.0f);
	case 'A': return std::make_pair<float, float>(6.0f, 56.0f);
	case 'B': return std::make_pair<float, float>(21.0f, 56.0f);
	case 'C': return std::make_pair<float, float>(37.0f, 56.0f);
	case 'D': return std::make_pair<float, float>(53.0f, 56.0f);
	case 'E': return std::make_pair<float, float>(69.0f, 56.0f);
	case 'F': return std::make_pair<float, float>(84.0f, 56.0f);
	case 'G': return std::make_pair<float, float>(101.0f, 56.0f);
	case 'H': return std::make_pair<float, float>(117.0f, 56.0f);
	case 'I': return std::make_pair<float, float>(129.0f, 56.0f);
	case 'J': return std::make_pair<float, float>(148.0f, 56.0f);
	case 'K': return std::make_pair<float, float>(165.0f, 56.0f);
	case 'L': return std::make_pair<float, float>(180.0f, 56.0f);
	case 'M': return std::make_pair<float, float>(198.0f, 56.0f);
	case 'N': return std::make_pair<float, float>(5.0f, 40.0f);
	case 'O': return std::make_pair<float, float>(21.0f, 40.0f);
	case 'P': return std::make_pair<float, float>(37.0f, 40.0f);
	case 'Q': return std::make_pair<float, float>(53.0f, 40.0f);
	case 'R': return std::make_pair<float, float>(70.0f, 40.0f);
	case 'S': return std::make_pair<float, float>(85.0f, 40.0f);
	case 'T': return std::make_pair<float, float>(101.0f, 40.0f);
	case 'U': return std::make_pair<float, float>(117.0f, 40.0f);
	case 'V': return std::make_pair<float, float>(134.0f, 40.0f);
	case 'W': return std::make_pair<float, float>(152.0f, 40.0f);
	case 'X': return std::make_pair<float, float>(165.0f, 40.0f);
	case 'Y': return std::make_pair<float, float>(181.0f, 40.0f);
	case 'Z': return std::make_pair<float, float>(197.0f, 40.0f);
	case '?': return std::make_pair<float, float>(4.0f, 8.0f);
	case '\'': return std::make_pair<float, float>(17.0f, 8.0f);
	case '*': return std::make_pair<float, float>(35.0f, 8.0f);
	case '#': return std::make_pair<float, float>(52.0f, 8.0f);
	case '"': return std::make_pair<float, float>(66.0f, 8.0f);
	case '%': return std::make_pair<float, float>(88.0f, 8.0f);
	case ':': return std::make_pair<float, float>(97.0f, 8.0f);
	case '(': return std::make_pair<float, float>(114.0f, 8.0f);
	case ')': return std::make_pair<float, float>(130.0f, 8.0f);
	case '/': return std::make_pair<float, float>(146.0f, 8.0f);
	case '-': return std::make_pair<float, float>(162.0f, 8.0f);
	case '+': return std::make_pair<float, float>(180.0f, 8.0f);
	case '=': return std::make_pair<float, float>(196.0f, 8.0f);
	}

	std::cout << "Error Char " << c << " not found!" << std::endl;
	return std::make_pair<float, float>(0, 0);
}
