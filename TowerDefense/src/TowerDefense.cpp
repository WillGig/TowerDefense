#include "pch.h"
#include "TowerDefense.h"
#include "scenes/Scene.h"
#include "scenes/MainMenu.h"
#include "scenes/Base.h"
#include "scenes/PreCombatScreen.h"
#include "scenes/PostCombatScreen.h"
#include "scenes/Combat.h"
#include "core/player.h"
#include "core/Board.h"
#include "cards/HeroCard.h"
#include "cards/TowerCards.h"
#include "core/TextureLoader.h"
#include "cards/SkillCards.h"
#include "cards/AuraCards.h"

void Update();
void Render();

GLFWwindow* window;
std::array<std::unique_ptr<TowerDefense::Scene>, 5> scenes;

int currentScene, day;
bool running;

//Initializes GLFW, GLEW, and objects needed for the game
bool TowerDefense::Init()
{
    int width = 1600, height = 1200;

    //GLFW Setup and Window Creation
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Tower Defense", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    //Center Window
    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (int)((vidmode->width - width) / 2), (int)((vidmode->height - height) / 2));

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    glfwSetCursorPosCallback(window, Input::cursor_position_callback);
    glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
    glfwSetScrollCallback(window, Input::scroll_callback);
    glfwSetWindowSizeCallback(window, Input::window_size_callback);

    //GLEW INitialization
    if (glewInit() != GLEW_OK)
        return false;

    std::cout << glGetString(GL_VERSION) << std::endl;

    //Setting Renderer Projection Matrix to game dimensions
    float scale;
    float hOffSet = 0.0f;
    float vOffSet = 0.0f;
    if ((float)height / 600.0f > (float)width / 800.0f)
    {
        scale = ((float)width / 800.0f);
        vOffSet = (height - 600.0f * scale) / (2 * scale);
    }
    else
    {
        scale = ((float)height / 600.0f);
        hOffSet = (width - 800.0f * scale) / (2 * scale);
    }

    Renderer::Get().SetProjectionMatrix(-hOffSet, 800.0f + hOffSet, -vOffSet, 600.0f + vOffSet, -1.0f, 1.0f);

    //Set Mouse Input dimensions
    Input::SetScale(scale, hOffSet, vOffSet, 600, window);

    LoadTextures();

    //Game Object Initialization
    std::cout << "Creating Scenes..." << std::endl;
    scenes = {
        std::make_unique<MainMenu>(),
        std::make_unique<Base>(),
        std::make_unique<PreCombatScreen>(),
        std::make_unique<Combat>(),
        std::make_unique<PostCombatScreen>()
    };
    currentScene = 0;
    day = 0;

    std::cout << "Setting Path..." << std::endl;
    const int path[] = { 0, 9, 0, 8, 0, 7, 1, 7, 2, 7, 3, 7, 4, 7, 4, 6, 4, 5, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5, 11, 5, 12, 5, 13, 5, 13, 4, 13, 3, 13, 2, 14, 2, 15, 2, 16, 2, 17, 2, 18, 2, 18, 1, 18, 0, 19, 0 };
    Board::Get().SetPath(path, sizeof(path));

    std::cout << "Generating Fights..." << std::endl;
    Combat::GenerateFights();

    //Starter Deck
    std::cout << "Creating Starter Deck..." << std::endl;
    Player& player = Player::Get();
    for (int i = 0; i < 8; i++)
        player.AddToDeck(std::make_shared<Focus>(false));
    for (int i = 0; i < 4; i++)
        player.AddToDeck(std::make_shared<ArcherCard>());
    for (int i = 0; i < 2; i++)
        player.AddToDeck(std::make_shared<PotOfGreed>());
    player.AddToDeck(std::make_shared<Envenom>());
    return true;
}

//Game Loop and Timer
void TowerDefense::Run()
{
    running = true;
    int frames = 0;
    int timer = 0;
    double delta = 0;
    auto previousTime = std::chrono::high_resolution_clock::now();

    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> timePassed = currentTime - previousTime;
        delta += timePassed.count() * 60.0;
        previousTime = currentTime;

        //Update 60 times per second
        if (delta > 1)
        {
            Update();
            delta--;
            timer++;
        }

        Render();
        frames++;

        //Print FPS once per second
        if (timer == 60)
        {
            timer -= 60;
           std::cout << frames << " FPS" << std::endl;
            frames = 0;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwWindowShouldClose(window))
            running = false;
    }
}

void TowerDefense::Stop()
{
    running = false;
}

//Called at end of program to clean up memory
//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
void TowerDefense::CleanUp()
{
    Player::Get().CleanUp();
    Board::Get().CleanUp();
    Base::CleanUp();
    Combat::CleanUp();
    Texture::FreeTextures();
    Shader::DeleteShaders();
    glfwTerminate();
}

void Render()
{
    Renderer::Get().Clear();
    scenes[currentScene]->Render();
}

void Update()
{
    scenes[currentScene]->Update();
    TowerDefense::Time::Get().Update();
}

void TowerDefense::SetScene(unsigned int scene) 
{
    if (scene < scenes.size())
    {
        currentScene = scene;
        scenes[scene]->OnSwitch();
    }
}

int TowerDefense::GetDay()
{
    return day;
}

void TowerDefense::NextDay()
{
    day++;
    Player::Get().UpdateDayText();
}