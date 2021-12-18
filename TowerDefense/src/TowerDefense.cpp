#include "pch.h"
#include "TowerDefense.h"
#include "scenes/Scene.h"
#include "scenes/MainMenu.h"
#include "scenes/NewGameMenu.h"
#include "scenes/LoadMenu.h"
#include "scenes/Settings.h"
#include "scenes/Base.h"
#include "scenes/Event.h"
#include "scenes/PreCombatScreen.h"
#include "scenes/PostCombatScreen.h"
#include "scenes/Combat.h"
#include "core/player.h"
#include "core/Board.h"
#include "core/TextureLoader.h"
#include "core/SaveLoad.h"

void Update();
void Render();

GLFWwindow* window;
std::array<std::unique_ptr<TowerDefense::Scene>, 9> scenes;

int currentScene, nextScene, day, frameCap;
bool running, showFPS;

float sceneFade, fadeSpeed;

std::unique_ptr<Text> fps;

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
    Scene::Init();
    scenes = {
        std::make_unique<MainMenu>(),
        std::make_unique<NewGameMenu>(),
        std::make_unique<LoadMenu>(),
        std::make_unique<Settings>(),
        std::make_unique<Base>(),
        std::make_unique<Event>(),
        std::make_unique<PreCombatScreen>(),
        std::make_unique<Combat>(),
        std::make_unique<PostCombatScreen>()
    };
    currentScene = 0;
    nextScene = 0;
    day = 0;
    showFPS = true;
    sceneFade = 1.0f;
    fadeSpeed = .05f;
    frameCap = 0;

    Load::LoadSettings();

    std::cout << "Setting Path..." << std::endl;
    const int path[] = { 0, 9, 0, 8, 0, 7, 1, 7, 2, 7, 3, 7, 4, 7, 4, 6, 4, 5, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5, 11, 5, 12, 5, 13, 5, 13, 4, 13, 3, 13, 2, 14, 2, 15, 2, 16, 2, 17, 2, 18, 2, 18, 1, 18, 0, 19, 0 };
    Board::Get().SetPath(path, sizeof(path));

    return true;
}

//Game Loop and Timer
void TowerDefense::Run()
{
    running = true;
    int frames = 0;
    int timer = 0;
    double delta1 = 0, delta2 = 0;
    auto previousTime = std::chrono::high_resolution_clock::now();

    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> timePassed = currentTime - previousTime;
        delta1 += timePassed.count() * 60.0;
        delta2 += timePassed.count() * (double)frameCap;

        previousTime = currentTime;

        //Update 60 times per second
        if (delta1 > 1)
        {
            Update();
            delta1--;
            timer++;
        }

        if (delta2 > 1 || frameCap == 0)
        {
            Render();
            frames++;
            if(frameCap != 0)
                delta2--;
        }
        

        //Calculate FPS once per second
        if (timer == 60)
        {
            timer -= 60;
            if (showFPS)
            {
                fps = std::make_unique<Text>(std::to_string(frames) + " FPS", 50.0f, 20.0f, 12.0f, 0.0f);
                fps->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
                fps->SetDropShadow(1.0f);
            }
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
    Artifact::CleanUp();
    RandomEvent::CleanUp();
    Scene::CleanUp();
    fps.reset();
    Texture::FreeTextures();
    Shader::DeleteShaders();
    glfwTerminate();
}

void Render()
{
    Renderer::Get().Clear();
    scenes[currentScene]->Render();
    if (sceneFade > 0.0f)
        TowerDefense::Scene::RenderFade(sceneFade);

    if (showFPS && fps)
        fps->Render();
}

void Update()
{
    scenes[currentScene]->Update();

    if (nextScene != currentScene)
    {
        if (sceneFade < 1.0f)
            sceneFade += fadeSpeed;
        else
        {
            currentScene = nextScene;
            scenes[currentScene]->OnSwitch();
        }
    }
    else if (sceneFade > 0.0f)
        sceneFade -= fadeSpeed;
    TowerDefense::Time::Get().Update();
}

void TowerDefense::SetScene(unsigned int scene) 
{
    if (scene < scenes.size())
        nextScene = scene;
}

int TowerDefense::GetDay()
{
    return day;
}

void TowerDefense::SetDay(int d)
{
    day = d;
}

void TowerDefense::NextDay()
{
    day++;
    Player::Get().UpdateDayText();
}

void TowerDefense::ResetDay()
{
    day = 0;
    Player::Get().UpdateDayText();
}

bool TowerDefense::FPSShowing()
{
    return showFPS;
}

void TowerDefense::ShowFPS(bool show)
{
    showFPS = show;
}

int TowerDefense::GetFrameCap()
{
    return frameCap;
}

void TowerDefense::SetFrameCap(int cap)
{
    frameCap = cap;
}