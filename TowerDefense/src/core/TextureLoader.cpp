#include "pch.h"
#include "TextureLoader.h"

//Load in all textures from spritesheets into texture cache
void TowerDefense::LoadTextures()
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
    Texture::LoadTexture("getResourcesButton",          baseButtons.load(0, 2));
    Texture::LoadTexture("getResourcesButtonSelected",  baseButtons.load(1, 2));
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
    Texture::LoadTexture("buildButton",                 baseButtons.load(0, 6));
    Texture::LoadTexture("buildButtonSelected",         baseButtons.load(1, 6));
    Texture::LoadTexture("exploreButton",               baseButtons.load(2, 6));
    Texture::LoadTexture("exploreButtonSelected",       baseButtons.load(3, 6));
    Texture::LoadTexture("mineButton",                  baseButtons.load(0, 7));
    Texture::LoadTexture("mineButtonSelected",          baseButtons.load(1, 7));
    Texture::LoadTexture("chopWoodButton",              baseButtons.load(2, 7));
    Texture::LoadTexture("chopWoodButtonSelected",      baseButtons.load(3, 7));
    Texture::LoadTexture("farmButton",                  baseButtons.load(0, 8));
    Texture::LoadTexture("farmButtonSelected",          baseButtons.load(1, 8));
    Texture::LoadTexture("backToMenuButton",            baseButtons.load(2, 8));
    Texture::LoadTexture("backToMenuButtonSelected",    baseButtons.load(3, 8));

    SpriteSheet buildButtons("res/textures/BuildButtons.png", 375, 65);
    Texture::LoadTexture("buildBed",                buildButtons.load(0, 0));
    Texture::LoadTexture("buildLibrary",            buildButtons.load(0, 1));
    Texture::LoadTexture("buildFishery",            buildButtons.load(0, 2));
    Texture::LoadTexture("buildChapel",             buildButtons.load(0, 3));
    Texture::LoadTexture("buildSmithy",             buildButtons.load(0, 4));
    Texture::LoadTexture("buildTavern",             buildButtons.load(0, 5));
    Texture::LoadTexture("buildBedSelected",        buildButtons.load(1, 0));
    Texture::LoadTexture("buildLibrarySelected",    buildButtons.load(1, 1));
    Texture::LoadTexture("buildFisherySelected",    buildButtons.load(1, 2));
    Texture::LoadTexture("buildChapelSelected",     buildButtons.load(1, 3));
    Texture::LoadTexture("buildSmithySelected",     buildButtons.load(1, 4));
    Texture::LoadTexture("buildTavernSelected",     buildButtons.load(1, 5));

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

    SpriteSheet combatRewardButton("res/textures/CombatRewardButton.png", 180, 50);
    Texture::LoadTexture("CombatReward",            combatRewardButton.load(0, 0));
    Texture::LoadTexture("CombatRewardSelected",    combatRewardButton.load(1, 0));

    SpriteSheet playerButtons("res/textures/PlayerButtons.png", 300, 300);
    Texture::LoadTexture("viewDeckButton",              playerButtons.load(0, 0));
    Texture::LoadTexture("viewDeckButtonSelected",      playerButtons.load(1, 0));
    Texture::LoadTexture("viewArtifactsButton",         playerButtons.load(0, 1));
    Texture::LoadTexture("viewArtifactsButtonSelected", playerButtons.load(1, 1));

    SpriteSheet statIcons("res/textures/Stats.png", 64, 64);
    Texture::LoadTexture("healthIcon",  statIcons.load(0, 0));
    Texture::LoadTexture("goldIcon",    statIcons.load(1, 0));
    Texture::LoadTexture("energyIcon",  statIcons.load(2, 0));
    Texture::LoadTexture("woodIcon",    statIcons.load(3, 0));
    Texture::LoadTexture("stoneIcon",   statIcons.load(4, 0));
    Texture::LoadTexture("wheatIcon",   statIcons.load(5, 0));

    SpriteSheet auras("res/textures/auras.png", 64, 64);
    Texture::LoadTexture("lifeSteal",       auras.load(0, 0));
    Texture::LoadTexture("poisonWeapons",   auras.load(1, 0));
    Texture::LoadTexture("stunAttacks",     auras.load(2, 0));
    Texture::LoadTexture("constantDamage",  auras.load(3, 0));
    Texture::LoadTexture("deathExplosions", auras.load(0, 1));
    Texture::LoadTexture("storm",           auras.load(1, 1));
    Texture::LoadTexture("enhancePoison",  auras.load(2, 1));

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
    Texture::LoadTexture("Rat",                     enemies.load(0, 0));
    Texture::LoadTexture("RatSelected",             enemies.load(1, 0));
    Texture::LoadTexture("Giant Rat",               enemies.load(2, 0));
    Texture::LoadTexture("Giant RatSelected",       enemies.load(3, 0));
    Texture::LoadTexture("Boss Rat",                enemies.load(4, 0));
    Texture::LoadTexture("Boss RatSelected",        enemies.load(5, 0));
    Texture::LoadTexture("Goblin",                  enemies.load(6, 0));
    Texture::LoadTexture("GoblinSelected",          enemies.load(7, 0));
    Texture::LoadTexture("Orc ",                    enemies.load(0, 1));
    Texture::LoadTexture("Orc Selected",            enemies.load(1, 1));
    Texture::LoadTexture("Beetle",                  enemies.load(2, 1));
    Texture::LoadTexture("BeetleSelected",          enemies.load(3, 1));
    Texture::LoadTexture("Slime",                   enemies.load(4, 1));
    Texture::LoadTexture("SlimeSelected",           enemies.load(5, 1));
    Texture::LoadTexture("Spider",                  enemies.load(6, 1));
    Texture::LoadTexture("SpiderSelected",          enemies.load(7, 1));
    Texture::LoadTexture("Tough Beetle",            enemies.load(0, 2));
    Texture::LoadTexture("Tough BeetleSelected",    enemies.load(1, 2));
    Texture::LoadTexture("Ooze",                    enemies.load(2, 2));
    Texture::LoadTexture("OozeSelected",            enemies.load(3, 2));
    Texture::LoadTexture("Mega Ooze",               enemies.load(4, 1));
    Texture::LoadTexture("Mega OozeSelected",       enemies.load(5, 1));
    Texture::LoadTexture("Double Ooze",             enemies.load(4, 2));
    Texture::LoadTexture("Double OozeSelected",     enemies.load(5, 2));
    Texture::LoadTexture("Jumping Ooze",            enemies.load(6, 2));
    Texture::LoadTexture("Jumping OozeSelected",    enemies.load(7, 2));
    Texture::LoadTexture("Doubler",                 enemies.load(0, 3));
    Texture::LoadTexture("DoublerSelected",         enemies.load(1, 3));
    Texture::LoadTexture("Shield Rat",              enemies.load(2, 3));
    Texture::LoadTexture("Shield RatSelected",      enemies.load(3, 3));
    Texture::LoadTexture("ShieldlessRat",           enemies.load(4, 3));
    Texture::LoadTexture("ShieldlessRatSelected",   enemies.load(5, 3));
    Texture::LoadTexture("Shaman Rat",              enemies.load(6, 3));
    Texture::LoadTexture("Shaman RatSelected",      enemies.load(7, 3));
    Texture::LoadTexture("Healer Rat",              enemies.load(6, 3));
    Texture::LoadTexture("Healer RatSelected",      enemies.load(7, 3));
    Texture::LoadTexture("Blink Bug",               enemies.load(0, 4));
    Texture::LoadTexture("Blink BugSelected",       enemies.load(1, 4));
    Texture::LoadTexture("Runner Beetle",           enemies.load(2, 4));
    Texture::LoadTexture("Runner BeetleSelected",   enemies.load(3, 4));
    Texture::LoadTexture("Tank Beetle",             enemies.load(4, 4));
    Texture::LoadTexture("Tank BeetleSelected",     enemies.load(5, 4));

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
    Texture::LoadTexture("fireBall",                skillCards.load(6, 0));
    Texture::LoadTexture("fireBallUpgraded",        skillCards.load(7, 0));
    Texture::LoadTexture("frostBall",               skillCards.load(8, 0));
    Texture::LoadTexture("frostBallUpgraded",       skillCards.load(9, 0));
    Texture::LoadTexture("lightning",               skillCards.load(10, 0));
    Texture::LoadTexture("lightningUpgraded",       skillCards.load(11, 0));
    Texture::LoadTexture("double",                  skillCards.load(0, 1));
    Texture::LoadTexture("doubleUpgraded",          skillCards.load(1, 1));
    Texture::LoadTexture("poisonBall",              skillCards.load(2, 1));
    Texture::LoadTexture("poisonBallUpgraded",      skillCards.load(3, 1));
    Texture::LoadTexture("sift",                    skillCards.load(4, 1));
    Texture::LoadTexture("siftUpgraded",            skillCards.load(5, 1));
    Texture::LoadTexture("reflect",                 skillCards.load(6, 1));
    Texture::LoadTexture("reflectUpgraded",         skillCards.load(7, 1));
    Texture::LoadTexture("skim",                    skillCards.load(8, 1));
    Texture::LoadTexture("skimUpgraded",            skillCards.load(9, 1));
    Texture::LoadTexture("refresh",                 skillCards.load(10, 1));
    Texture::LoadTexture("refreshUpgraded",         skillCards.load(11, 1));
    Texture::LoadTexture("center",                  skillCards.load(0, 2));
    Texture::LoadTexture("centerUpgraded",          skillCards.load(1, 2));
    Texture::LoadTexture("gather",                  skillCards.load(2, 2));
    Texture::LoadTexture("gatherUpgraded",          skillCards.load(3, 2));
    Texture::LoadTexture("concentrate",             skillCards.load(4, 2));
    Texture::LoadTexture("concentrateUpgraded",     skillCards.load(5, 2));
    Texture::LoadTexture("recharge",                skillCards.load(6, 2));
    Texture::LoadTexture("rechargeUpgraded",        skillCards.load(7, 2));
    Texture::LoadTexture("attain",                  skillCards.load(8, 2));
    Texture::LoadTexture("attainUpgraded",          skillCards.load(9, 2));
    Texture::LoadTexture("ren",                     skillCards.load(10, 2));
    Texture::LoadTexture("renUpgraded",             skillCards.load(11, 2));
    Texture::LoadTexture("surge",                   skillCards.load(0, 3));
    Texture::LoadTexture("surgeUpgraded",           skillCards.load(1, 3));
    Texture::LoadTexture("massStun",                skillCards.load(2, 3));
    Texture::LoadTexture("massStunUpgraded",        skillCards.load(3, 3));

    SpriteSheet auraCards("res/textures/AuraCards.png", 440, 560);
    Texture::LoadTexture("lifeAura",                    auraCards.load(0, 0));
    Texture::LoadTexture("lifeAuraUpgraded",            auraCards.load(1, 0));
    Texture::LoadTexture("envenom",                     auraCards.load(2, 0));
    Texture::LoadTexture("envenomUpgraded",             auraCards.load(3, 0));
    Texture::LoadTexture("stunningStrikes",             auraCards.load(4, 0));
    Texture::LoadTexture("stunningStrikesUpgraded",     auraCards.load(5, 0));
    Texture::LoadTexture("theFloorIsLava",              auraCards.load(6, 0));
    Texture::LoadTexture("theFloorIsLavaUpgraded",      auraCards.load(7, 0));
    Texture::LoadTexture("strongPoisons",               auraCards.load(0, 1));
    Texture::LoadTexture("strongPoisonsUpgraded",       auraCards.load(1, 1));
    Texture::LoadTexture("explosiveStrikes",            auraCards.load(2, 1));
    Texture::LoadTexture("explosiveStrikesUpgraded",    auraCards.load(3, 1));
    Texture::LoadTexture("lightningStorm",              auraCards.load(4, 1));
    Texture::LoadTexture("lightningStormUpgraded",      auraCards.load(5, 1));

    SpriteSheet curses("res/textures/Curses.png", 440, 560);
    Texture::LoadTexture("Flames",          curses.load(0, 0));
    Texture::LoadTexture("FlamesUpgraded",  curses.load(1, 0));

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
    Texture::LoadTexture("exhaustInfo",     cardInfo.load(3, 3));
    Texture::LoadTexture("poisonInfo",      cardInfo.load(0, 4));
    Texture::LoadTexture("auraInfo",        cardInfo.load(1, 4));
    Texture::LoadTexture("stunInfo",        cardInfo.load(2, 4));
    Texture::LoadTexture("slowInfo",        cardInfo.load(3, 4));

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
    Texture::LoadTexture("damageUpgrade",       heroUpgrades.load(0, 0));
    Texture::LoadTexture("rangeUpgrade",        heroUpgrades.load(1, 0));
    Texture::LoadTexture("attackSpeedUpgrade",  heroUpgrades.load(2, 0));
    Texture::LoadTexture("moremissiles",        heroUpgrades.load(3, 0));

    std::cout << "...Artifacts" << std::endl;

    SpriteSheet artifacts("res/textures/Artifacts.png", 256, 256);
    Texture::LoadTexture("Token Of The Mute",       artifacts.load(0, 0));
    Texture::LoadTexture("Token Of The Armored",    artifacts.load(1, 0));
    Texture::LoadTexture("Token Of The Broken",     artifacts.load(2, 0));
    Texture::LoadTexture("Token Of The Vigilant",   artifacts.load(3, 0));
    Texture::LoadTexture("Blessing of the Bat",     artifacts.load(4, 0));

    SpriteSheet artifactInfo("res/textures/ArtifactInfo.png", 440, 170);
    Texture::LoadTexture("Token Of The MuteInfo",       artifactInfo.load(0, 0));
    Texture::LoadTexture("Token Of The ArmoredInfo",    artifactInfo.load(1, 0));
    Texture::LoadTexture("Token Of The BrokenInfo",     artifactInfo.load(2, 0));
    Texture::LoadTexture("Token Of The VigilantInfo",   artifactInfo.load(3, 0));
    Texture::LoadTexture("Blessing of the BatInfo",     artifactInfo.load(0, 1));

    std::cout << "...Animations" << std::endl;

    SpriteSheet animationEffects("res/textures/AnimationEffects.png", 700, 100);
    Texture::LoadTexture("fireExplosion",       animationEffects.load(0, 0));
    Texture::LoadTexture("frostExplosion",      animationEffects.load(0, 1));
    Texture::LoadTexture("acidExplosion",       animationEffects.load(0, 2));
    Texture::LoadTexture("smiteAnimation",      animationEffects.load(0, 3));
    Texture::LoadTexture("critAnimation",       animationEffects.load(0, 4));
    Texture::LoadTexture("shamanAura",          animationEffects.load(0, 5));
    Texture::LoadTexture("healingAura",         animationEffects.load(0, 6));
}