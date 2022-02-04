#include "pch.h"
#include "Board.h"
#include "TowerDefense.h"
#include "Player.h"

#define EMPTY   0xffffff
#define PATH    0xffff00
#define START   0x00ff00
#define END     0xff0000
#define ROCK    0xA5A5A5
#define TREE    0x007F0E

int TowerDefense::Board::TILESIZE = 32;

TowerDefense::Board::Board(int width, int height)
    :m_X((800.0f - TILESIZE * width) / 2.0f), m_Y(TILESIZE * 7.8f), m_Width(width), m_Height(height),
    m_TileSelected(false), m_CurrentTile(), 
    m_SelectedTile(std::make_shared<StaticImage>(0.0f, 0.0f, TILESIZE, TILESIZE, 0.0f, "selectedTile")),
    m_Tiles(std::make_shared<std::vector<std::shared_ptr<Tile>>>()), 
    m_Positions(std::make_unique<float[]>(width* height * 16)),
    m_Path(), m_Position(m_X, m_Y, 0.0f)
{
    //Setting index buffer size based on number of tiles
    std::unique_ptr<unsigned int[]> indices = std::make_unique<unsigned int[]>(width * height * 6);

    //positions of a single tile that will be added to the vertex buffer data
    std::unique_ptr<float[]> tempPositions;

    //Offset of current tile
    int xOffSet = 0;
    int yOffSet = 0;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            // Get vertex data for current tile
            // Set by default to tile 0
            tempPositions = GetPositions(0, xOffSet, yOffSet);
            for (int k = 0; k < 16; k++)
            {
                m_Positions[(i+j*width) * 16 + k] = tempPositions[k];
            }

            //Add indicies for the tile to the index buffer
            for (int k = 0; k < 6; k++)
            {
                if (k < 3)
                    indices[k + (i + j * width) * 6] = k + (i + j * width) * 4;
                else
                    indices[k + (i + j * width) * 6] = (k - 1) % 4 + (i + j * width) * 4;
            }
            xOffSet += TILESIZE;

            m_Tiles->push_back(std::make_shared<Tile>(m_X + i * TILESIZE, m_Y + j * TILESIZE, TILESIZE, TILESIZE));
        }
        yOffSet += TILESIZE;
        xOffSet = 0;
    }

    m_VAO = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(&m_Positions[0], width * height * 16 * sizeof(float), true);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], width * height * 6);

    m_Shader = Shader::GetShader("res/shaders/Texture.Shader");
    m_Shader->Bind();
    m_Texture = Texture::GetTexture("tiles");
    m_Shader->SetUniform1i("u_Texture", 0);
}

TowerDefense::Board& TowerDefense::Board::Get()
{
    static TowerDefense::Board instance(20, 10);
    return instance;
}

//Go through each tile and find the current tile. If a tower is being held or placed, update the selectedTile position
void TowerDefense::Board::Update()
{
    m_TileSelected = false;
    m_CurrentTile.reset();

    for (unsigned int i = 0; i < m_Tiles->size(); i++)
    {
        if (m_Tiles->at(i)->Contains(Input::GetMouseX(), Input::GetMouseY()))
        {
            m_CurrentTile = m_Tiles->at(i);

            if (Player::Get().GetHand()->GetSelectedCard() != -1 && !Player::Get().GetHand()->ShowingCardInfo()) {
                m_TileSelected = true;

                float selectedTileX, selectedTileY;

                if (Input::GetMouseX() - m_CurrentTile->GetX() > 0.0f) {
                    selectedTileX = m_CurrentTile->GetX() + TILESIZE / 2 * (m_SelectedTile->GetWidth()/TILESIZE - 1);
                }
                else {
                    selectedTileX = m_CurrentTile->GetX() - TILESIZE / 2 * (m_SelectedTile->GetWidth() / TILESIZE - 1);
                }

                if (Input::GetMouseY() - m_CurrentTile->GetY() > 0.0f) {
                    selectedTileY = m_CurrentTile->GetY() + TILESIZE / 2 * (m_SelectedTile->GetHeight() / TILESIZE - 1);;
                }
                else {
                    selectedTileY = m_CurrentTile->GetY() - TILESIZE / 2 * (m_SelectedTile->GetHeight() / TILESIZE - 1);;
                }

                m_SelectedTile->SetX(selectedTileX);
                m_SelectedTile->SetY(selectedTileY);
            }
        }
    }
}

void TowerDefense::Board::Render()
{
    m_Texture->Bind();
    {
        Mat4f mvp = Renderer::Get().GetProjectionMatrix() * Mat4f::Translate(m_Position);
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        Renderer::Get().Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    if (m_TileSelected)
        m_SelectedTile->Render();
}

void TowerDefense::Board::LoadMap(const std::string& file)
{
    stbi_set_flip_vertically_on_load(0);

    int width, height, channels;
    //Load map data
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &channels, 3);

    //Verify data loaded
    if (!data)
    {
        std::cout << "Failed to load map " << file << std::endl;
        std::cout << "Loading default map" << std::endl;
        LoadMap("res/maps/map0.png");
        return;
    }

    //Verify map dimensions
    if (width != m_Width || height != m_Height)
    {
        std::cout << "Invalid map dimensions for map " << file << std::endl;
        std::cout << "Loading default map" << std::endl;
        LoadMap("res/maps/map0.png");
        stbi_image_free(data);
        return;
    }

    //Load all tile images and set occupied tiles
    int startX = -1, startY = -1, endX = -1, endY = -1;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r = data[(x + y * width) * channels];
            int g = data[(x + y * width) * channels + 1];
            int b = data[(x + y * width) * channels + 2];

            long rgb = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);

            int bX = x;
            int bY = height - 1 - y;

            switch (rgb)
            {
            case START:
                SetTileImage(bX, bY, 1);
                m_Tiles->at(bX + bY * m_Width)->SetOccupied(true);
                startX = x;
                startY = y;
                break;
            case END:
                SetTileImage(bX, bY, 1);
                m_Tiles->at(bX + bY * m_Width)->SetOccupied(true);
                endX = x;
                endY = y;
                break;
            case PATH:
                SetTileImage(bX, bY, 1);
                m_Tiles->at(bX + bY * m_Width)->SetOccupied(true);
                break;
            case ROCK:
                SetTileImage(bX, bY, 2);
                m_Tiles->at(bX + bY * m_Width)->SetOccupied(true);
                break;
            case TREE:
                SetTileImage(bX, bY, 3);
                m_Tiles->at(bX + bY * m_Width)->SetOccupied(true);
                break;
            default:
                SetTileImage(bX, bY, 0);
                m_Tiles->at(bX + bY * m_Width)->SetOccupied(false);
            }
        }
    }

    //Verify that path has start and end tiles
    if (startX == -1)
    {
        std::cout << "Failed to find path start for map " << file << std::endl;
        stbi_image_free(data);
        std::cout << "Loading default map" << std::endl;
        LoadMap("res/maps/map0.png");
        return;
    }
    else if (endX == -1)
    {
        std::cout << "Failed to find path end for map " << file << std::endl;
        stbi_image_free(data);
        std::cout << "Loading default map" << std::endl;
        LoadMap("res/maps/map0.png");
        return;
    }

    //Load path
    int currentX = startX;
    int currentY = startY;
    int previousDirection = -1;
    m_Path = std::make_shared<std::vector<int>>();
    while (currentX != endX || currentY != endY)
    {
        m_Path->push_back(currentX);
        m_Path->push_back(m_Height - 1 - currentY);

        //find direction of path
        for (int i = 0; i < 5; i++)
        {
            //All directions have been checked and no path tile was found
            if (i == 4)
            {
                std::cout << "Error: path end not found" << std::endl;
                stbi_image_free(data);
                std::cout << "Loading default map" << std::endl;
                LoadMap("res/maps/map0.png");
                return;
            }

            int direction;
            if (previousDirection > -1)
                direction = (previousDirection + i) % 4; //Check forward first
            else
                direction = i % 4;

            if (previousDirection == (direction + 2) % 4) //Skip the previous path tile
                continue;

            int xPos = currentX + (int)sin(direction * (PI / 2.0f));
            int yPos = currentY + (int)cos(direction * (PI / 2.0f));

            //Bounds checking
            if (xPos < 0 || xPos > m_Width || yPos < 0 || yPos > m_Height)
                continue;

            int r = data[(xPos + yPos * width) * channels];
            int g = data[(xPos + yPos * width) * channels + 1];
            int b = data[(xPos + yPos * width) * channels + 2];
            long rgb = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);

            //Move to next tile in path
            if (rgb == PATH || rgb == END)
            {
                currentX = xPos;
                currentY = yPos;
                previousDirection = direction;
                break;
            }
        }
    }
    //Add end tile
    m_Path->push_back(currentX);
    m_Path->push_back(m_Height - 1 - currentY);

    stbi_image_free(data);
}

void TowerDefense::Board::LoadRandomMap()
{
    int numMaps = 0;
    bool exists = true;
    while (exists)
    {
        std::ifstream file("res/maps/map" + std::to_string(numMaps) + ".png");
        
        exists = (bool)file;
        
        if (exists)
        {
            numMaps++;
            file.close();
        }
    }

    if (numMaps == 0)
    {
        std::cout << "Error: No map files found" << std::endl;
        return;
    }
   
    int map = (int)(Random::GetFloat() * numMaps);
    LoadMap("res/maps/map" + std::to_string(map) + ".png");
}

bool TowerDefense::Board::Contains(float x, float y) const
{
    float width = (float)(m_Width * TILESIZE);
    float height = (float)(m_Height * TILESIZE);
    return !(x < m_X  - TILESIZE/2 || x > m_X + width - TILESIZE/2 || y < m_Y - TILESIZE/2 || y > m_Y + height - TILESIZE/2);
}

void TowerDefense::Board::SetSelectedTileSize(int width, int height)
{
    m_SelectedTile->SetWidth(width);
    m_SelectedTile->SetHeight(height);
}

//Returns true if the currently held tower can fit in the selected space
bool TowerDefense::Board::ValidPlace()
{
    if (!m_CurrentTile)
        return false;

    if (m_SelectedTile->GetX() - m_SelectedTile->GetWidth()/2 < m_X - TILESIZE/2 || m_SelectedTile->GetX() + m_SelectedTile->GetWidth()/2 > m_X + m_Width * TILESIZE)
        return false;
        
    if (m_SelectedTile->GetY() - m_SelectedTile->GetHeight()/2 < m_Y - TILESIZE/2 || m_SelectedTile->GetY() + m_SelectedTile->GetHeight()/2 > m_Y + m_Height * TILESIZE)
        return false;

    int sX = (int)m_SelectedTile->GetX();
    int sY = (int)m_SelectedTile->GetY();
    int sW = m_SelectedTile->GetWidth();
    int sH = m_SelectedTile->GetHeight();
    for (unsigned int i = 0; i < m_Tiles->size(); i++) {
        
        int tX = (int)m_Tiles->at(i)->GetX();
        int tY = (int)m_Tiles->at(i)->GetY();

        if (tX > sX - sW /2 && tX < sX + sW /2 && tY > sY - sH /2 && tY < sY + sH /2) {
            if (m_Tiles->at(i)->IsOccupied())
                return false;
        }
    }

    return true;
}

//Called at end of program to clean up memory
//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
void TowerDefense::Board::CleanUp()
{
    m_CurrentTile.reset();
    m_SelectedTile.reset();
    m_Tiles.reset();
    m_Path.reset();
    m_VAO.reset();
    m_VertexBuffer.reset();
    m_IndexBuffer.reset();
    m_Shader.reset();
    m_Texture.reset();
}

void TowerDefense::Board::SetTileImage(int x, int y, int tileImage)
{
    //Update vertex coordinates of selected tile to new tile image on sheet
    std::unique_ptr<float[]> tempPositions = GetPositions(tileImage, x * TILESIZE, y * TILESIZE);
    for (int i = 0; i < 16; i++)
    {
        m_Positions[(x + y * m_Width) * 16 + i] = tempPositions[i];
    }

    m_VertexBuffer->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Width * m_Height * 16 * sizeof(float), &m_Positions[0]);
}

//Returns vertex positions of the given tile 
std::unique_ptr<float[]> TowerDefense::Board::GetPositions(unsigned int tileNumber, int xOff, int yOff)
{
    float width = (float)TILESIZE;
    float height = (float)TILESIZE;
    auto coords = GetCoords(tileNumber);

    std::unique_ptr<float[]> pos = std::make_unique<float[]>(16);

    pos[0] = (-width / 2 + xOff);
    pos[1] = (-height / 2 + yOff);
    pos[2] = ((coords.first - width / 2) / 128.0f);
    pos[3] = ((coords.second - height / 2) / 32.0f);
    pos[4] = (width / 2 + xOff);
    pos[5] = (-height / 2 + yOff);
    pos[6] = ((coords.first + width / 2) / 128.0f);
    pos[7] = ((coords.second - height / 2) / 32.0f);
    pos[8] = (width / 2 + xOff);
    pos[9] = (height / 2 + yOff);
    pos[10] = ((coords.first + width / 2) / 128.0f);
    pos[11] = ((coords.second + height / 2) / 32.0f);
    pos[12] = (-width / 2 + xOff);
    pos[13] = (height / 2 + yOff);
    pos[14] = ((coords.first - width / 2) / 128.0f);
    pos[15] = ((coords.second + height / 2) / 32.0f);

    return pos;
}

//Hardcoded values of centers of tile positions on tile sheet
std::pair<float, float> TowerDefense::Board::GetCoords(unsigned int tileNumber)
{
    switch (tileNumber)
    {
    case 0: return std::make_pair<float, float>(16.0f, 16.0f);
    case 1: return std::make_pair<float, float>(48.0f, 16.0f);
    case 2: return std::make_pair<float, float>(80.0f, 16.0f);
    case 3: return std::make_pair<float, float>(112.0f, 16.0f);
    }

    std::cout << "Error Tile " << tileNumber << " not found!" << std::endl;
    return std::make_pair<float, float>(0, 0);
}
