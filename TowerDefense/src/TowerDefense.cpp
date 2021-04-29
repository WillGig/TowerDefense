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
#include "cards/Focus.h"
#include "cards/PotOfGreed.h"
#include "cards/FireBall.h"
#include "cards/FrostBall.h"
#include "cards/HeroCard.h"
#include "cards/TowerCards.h"

void Update();
void Render();
void LoadTextures();

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

    //Starter Artifacts
    player.AddToArtifacts(std::make_shared<TokenOfTheMute>());
    player.AddToArtifacts(std::make_shared<TokenOfTheArmored>());

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

void LoadTextures()
{
    std::cout << "Loading..." << std::endl;

    std::cout << "...Buttons" << std::endl;

    SpriteSheet mainMenuButtons("res/textures/MainMenuButtons.png", 200, 50);
    Texture::LoadTexture("newGameButton",           mainMenuButtons.load(0, 0));
    Texture::LoadTexture("newGameButtonSelected",   mainMenuButtons.load(1, 0));
    Texture::LoadTexture("loadGameButton",          mainMenuButtons.load(0, 1));
    Texture::LoadTexture("loadGameButtonSelected",  mainMenuButtons.load(1, 1));
    Texture::LoadTexture("settingsButton",          mainMenuButtons.load(0, 2));
    Texture::LoadTexture("settingsButtonSelected",  mainMenuButtons.load(1, 2));
    Texture::LoadTexture("exitButton",              mainMenuButtons.load(0, 3));
    Texture::LoadTexture("exitButtonSelected",      mainMenuButtons.load(1, 3));

    SpriteSheet baseButtons("res/textures/BaseButtons.png", 180, 50);
    Texture::LoadTexture("confirmButton",               baseButtons.load(0, 0));
    Texture::LoadTexture("confirmButtonSelected",       baseButtons.load(1, 0));
    Texture::LoadTexture("cancelButton",                baseButtons.load(2, 0));
    Texture::LoadTexture("cancelButtonSelected",        baseButtons.load(3, 0));
    Texture::LoadTexture("nextDayButton",               baseButtons.load(0, 1));
    Texture::LoadTexture("nextDayButtonSelected",       baseButtons.load(1, 1));
    Texture::LoadTexture("restButton",                  baseButtons.load(2, 1));
    Texture::LoadTexture("restButtonSelected",          baseButtons.load(3, 1));
    Texture::LoadTexture("exploreCavesButton",          baseButtons.load(0, 2));
    Texture::LoadTexture("exploreCavesButtonSelected",  baseButtons.load(1, 2));
    Texture::LoadTexture("goFishingButton",             baseButtons.load(2, 2));
    Texture::LoadTexture("goFishingButtonSelected",     baseButtons.load(3, 2));
    Texture::LoadTexture("visitLibraryButton",          baseButtons.load(0, 3));
    Texture::LoadTexture("visitLibraryButtonSelected",  baseButtons.load(1, 3));
    Texture::LoadTexture("smithButton",                 baseButtons.load(2, 3));
    Texture::LoadTexture("smithButtonSelected",         baseButtons.load(3, 3));
    Texture::LoadTexture("goTavernButton",              baseButtons.load(0, 4));
    Texture::LoadTexture("goTavernButtonSelected",      baseButtons.load(1, 4));
    Texture::LoadTexture("beginCombatButton",           baseButtons.load(2, 4));
    Texture::LoadTexture("beginCombatButtonSelected",   baseButtons.load(3, 4));
    Texture::LoadTexture("returnToCampButton",          baseButtons.load(0, 5));
    Texture::LoadTexture("returnToCampButtonSelected",  baseButtons.load(1, 5));
    Texture::LoadTexture("prayButton",                  baseButtons.load(2, 5));
    Texture::LoadTexture("prayButtonSelected",          baseButtons.load(3, 5));

    SpriteSheet combatButtons("res/textures/CombatButtons.png", 384, 128);
    Texture::LoadTexture("startButton",         combatButtons.load(0, 0));
    Texture::LoadTexture("startButtonSelected", combatButtons.load(1, 0));
    Texture::LoadTexture("pause",               combatButtons.load(2, 0));
    Texture::LoadTexture("pauseSelected",       combatButtons.load(3, 0));
    Texture::LoadTexture("endButton",           combatButtons.load(0, 1));
    Texture::LoadTexture("endButtonSelected",   combatButtons.load(1, 1));
    Texture::LoadTexture("speed1",              combatButtons.load(2, 1));
    Texture::LoadTexture("speed1Selected",      combatButtons.load(3, 1));
    Texture::LoadTexture("speed2",              combatButtons.load(0, 2));
    Texture::LoadTexture("speed2Selected",      combatButtons.load(1, 2));
    Texture::LoadTexture("speed3",              combatButtons.load(2, 2));
    Texture::LoadTexture("speed3Selected",      combatButtons.load(3, 2));

    SpriteSheet eventButtons("res/textures/EventButtons.png", 600, 50);
    Texture::LoadTexture("eventButton",         eventButtons.load(0, 0));
    Texture::LoadTexture("eventButtonSelected", eventButtons.load(0, 1));

    SpriteSheet PlayerButtons("res/textures/PlayerButtons.png", 300, 300);
    Texture::LoadTexture("viewDeckButton",              PlayerButtons.load(0, 0));
    Texture::LoadTexture("viewDeckButtonSelected",      PlayerButtons.load(1, 0));
    Texture::LoadTexture("viewArtifactsButton",         PlayerButtons.load(0, 1));
    Texture::LoadTexture("viewArtifactsButtonSelected", PlayerButtons.load(1, 1));

    std::cout << "...Towers" << std::endl;

    SpriteSheet towers("res/textures/Towers.png", 64, 64);
    Texture::LoadTexture("Archer",                  towers.load(0, 0));
    Texture::LoadTexture("ArcherHighlighted",       towers.load(1, 0));
    Texture::LoadTexture("Wizard",                  towers.load(2, 0));
    Texture::LoadTexture("WizardHighlighted",       towers.load(3, 0));
    Texture::LoadTexture("Alchemist",               towers.load(0, 1));
    Texture::LoadTexture("AlchemistHighlighted",    towers.load(1, 1));
    Texture::LoadTexture("Bard",                    towers.load(2, 1));
    Texture::LoadTexture("BardHighlighted",         towers.load(3, 1));
    Texture::LoadTexture("Cleric",                  towers.load(0, 2));
    Texture::LoadTexture("ClericHighlighted",       towers.load(1, 2));
    Texture::LoadTexture("Paladin",                 towers.load(2, 2));
    Texture::LoadTexture("PaladinHighlighted",      towers.load(3, 2));
    Texture::LoadTexture("GIANT",                   towers.load(0, 3));
    Texture::LoadTexture("GIANTHighlighted",        towers.load(1, 3));
    Texture::LoadTexture("Monk",                    towers.load(2, 3));
    Texture::LoadTexture("MonkHighlighted",         towers.load(3, 3));

    std::cout << "...Enemies" << std::endl;

    SpriteSheet enemies("res/textures/Enemies.png", 64, 64);
    Texture::LoadTexture("Rat",                 enemies.load(0, 0));
    Texture::LoadTexture("RatSelected",         enemies.load(1, 0));
    Texture::LoadTexture("Giant Rat",            enemies.load(2, 0));
    Texture::LoadTexture("Giant RatSelected",    enemies.load(3, 0));
    Texture::LoadTexture("Boss Rat",             enemies.load(0, 1));
    Texture::LoadTexture("Boss RatSelected",     enemies.load(1, 1));
    Texture::LoadTexture("Goblin",              enemies.load(2, 1));
    Texture::LoadTexture("GoblinSelected",      enemies.load(3, 1));
    Texture::LoadTexture("Orc ",                 enemies.load(0, 2));
    Texture::LoadTexture("Orc Selected",         enemies.load(1, 2));

    std::cout << "...Cards" << std::endl;

    SpriteSheet towerCards("res/textures/TowerCards.png", 440, 560);
    Texture::LoadTexture("archerCard",              towerCards.load(0, 0));
    Texture::LoadTexture("archerCardUpgraded",      towerCards.load(1, 0));
    Texture::LoadTexture("wizardCard",              towerCards.load(2, 0));
    Texture::LoadTexture("wizardCardUpgraded",      towerCards.load(3, 0));
    Texture::LoadTexture("alchemistCard",           towerCards.load(4, 0));
    Texture::LoadTexture("alchemistCardUpgraded",   towerCards.load(5, 0));
    Texture::LoadTexture("bardCard",                towerCards.load(0, 1));
    Texture::LoadTexture("bardCardUpgraded",        towerCards.load(1, 1));
    Texture::LoadTexture("clericCard",              towerCards.load(2, 1));
    Texture::LoadTexture("clericCardUpgraded",      towerCards.load(3, 1));
    Texture::LoadTexture("paladinCard",             towerCards.load(4, 1));
    Texture::LoadTexture("paladinCardUpgraded",     towerCards.load(5, 1));
    Texture::LoadTexture("giantCard",               towerCards.load(0, 2));
    Texture::LoadTexture("giantCardUpgraded",       towerCards.load(1, 2));
    Texture::LoadTexture("monkCard",                towerCards.load(2, 2));
    Texture::LoadTexture("monkCardUpgraded",        towerCards.load(3, 2));

    SpriteSheet skillCards("res/textures/SkillCards.png", 440, 560);
    Texture::LoadTexture("focus",                   skillCards.load(0, 0));
    Texture::LoadTexture("focusUpgraded",           skillCards.load(1, 0));
    Texture::LoadTexture("focusExhausts",           skillCards.load(2, 0));
    Texture::LoadTexture("focusExhaustsUpgraded",   skillCards.load(3, 0));
    Texture::LoadTexture("potOfGreed",              skillCards.load(4, 0));
    Texture::LoadTexture("potOfGreedUpgraded",      skillCards.load(5, 0));
    Texture::LoadTexture("fireBall",                skillCards.load(0, 1));
    Texture::LoadTexture("fireBallUpgraded",        skillCards.load(1, 1));
    Texture::LoadTexture("frostBall",               skillCards.load(2, 1));
    Texture::LoadTexture("frostBallUpgraded",       skillCards.load(3, 1));

    SpriteSheet curses("res/textures/Curses.png", 440, 560);
    Texture::LoadTexture("Flames",                  curses.load(0, 0));
    Texture::LoadTexture("FlamesUpgraded",          curses.load(1, 0));

    SpriteSheet cardInfo("res/textures/InfoTiles.png", 440, 170);
    Texture::LoadTexture("SummonInfo",      cardInfo.load(0, 0));
    Texture::LoadTexture("UpgradedInfo",    cardInfo.load(1, 0));
    Texture::LoadTexture("Human",           cardInfo.load(2, 0));
    Texture::LoadTexture("Dwarf",           cardInfo.load(3, 0));
    Texture::LoadTexture("High Elf",        cardInfo.load(0, 1));
    Texture::LoadTexture("Wood Elf",        cardInfo.load(1, 1));
    Texture::LoadTexture("Gnome",           cardInfo.load(2, 1));
    Texture::LoadTexture("Orc",             cardInfo.load(3, 1));
    Texture::LoadTexture("Giant",           cardInfo.load(0, 2));
    Texture::LoadTexture("Explorer",        cardInfo.load(1, 2));
    Texture::LoadTexture("Battle Ready",    cardInfo.load(2, 2));
    Texture::LoadTexture("Veteran",         cardInfo.load(3, 2));
    Texture::LoadTexture("Just Lucky",      cardInfo.load(0, 3));
    Texture::LoadTexture("Farsighted",      cardInfo.load(1, 3));
    Texture::LoadTexture("Nearsighted",     cardInfo.load(2, 3));

    SpriteSheet heroImages("res/textures/HeroImages.png", 440, 560);
    Texture::LoadTexture("humanMale",       heroImages.load(0, 0));
    Texture::LoadTexture("humanFemale",     heroImages.load(1, 0));
    Texture::LoadTexture("dwarfMale",       heroImages.load(2, 0));
    Texture::LoadTexture("dwarfFemale",     heroImages.load(3, 0));
    Texture::LoadTexture("highElfMale",     heroImages.load(4, 0));
    Texture::LoadTexture("highElfFemale",   heroImages.load(5, 0));
    Texture::LoadTexture("woodElfMale",     heroImages.load(0, 1));
    Texture::LoadTexture("woodElfFemale",   heroImages.load(1, 1));
    Texture::LoadTexture("gnomeMale",       heroImages.load(2, 1));
    Texture::LoadTexture("gnomeFemale",     heroImages.load(3, 1));
    Texture::LoadTexture("orcMale",         heroImages.load(4, 1));
    Texture::LoadTexture("orcFemale",       heroImages.load(5, 1));
    Texture::LoadTexture("giantMale",       heroImages.load(0, 2));
    Texture::LoadTexture("giantFemale",     heroImages.load(1, 2));

    SpriteSheet heroUpgrades("res/textures/HeroUpgrades.png", 440, 560);
    Texture::LoadTexture("damageUpgrade", heroUpgrades.load(0, 0));
    Texture::LoadTexture("rangeUpgrade", heroUpgrades.load(1, 0));
    Texture::LoadTexture("attackSpeedUpgrade", heroUpgrades.load(2, 0));
    Texture::LoadTexture("moremissiles", heroUpgrades.load(3, 0));

    std::cout << "...Artifacts" << std::endl;

    SpriteSheet artifacts("res/textures/Artifacts.png", 64, 64);
    Texture::LoadTexture("TokenOfTheMute",      artifacts.load(0, 0));
    Texture::LoadTexture("TokenOfTheArmored",   artifacts.load(1, 0));

    SpriteSheet artifactInfo("res/textures/ArtifactInfo.png", 440, 170);
    Texture::LoadTexture("TokenOfTheMuteInfo",      artifactInfo.load(0, 0));
    Texture::LoadTexture("TokenOfTheArmoredInfo",   artifactInfo.load(1, 0));

    std::cout << "...Animations" << std::endl;

    SpriteSheet animationEffects("res/textures/AnimationEffects.png", 700, 100);
    Texture::LoadTexture("fireExplosion",   animationEffects.load(0, 0));
    Texture::LoadTexture("frostExplosion",  animationEffects.load(0, 1));
    Texture::LoadTexture("acidExplosion",   animationEffects.load(0, 2));
    Texture::LoadTexture("smiteAnimation",  animationEffects.load(0, 3));
    Texture::LoadTexture("critAnimation",   animationEffects.load(0, 4));
}