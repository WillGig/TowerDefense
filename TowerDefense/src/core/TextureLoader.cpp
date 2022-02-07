#include "pch.h"
#include "TextureLoader.h"

std::string loadCategory;

//Load in all textures from spritesheets into texture cache
void TowerDefense::LoadingScreen::LoadTextures(GLFWwindow* w)
{
    loadCategory = "Buttons";

    SpriteSheet mainMenuButtons("res/textures/MainMenuButtons.png", 200, 50);
    Load("newGameButton",           mainMenuButtons.load(0, 0), w);
    Load("newGameButtonSelected",   mainMenuButtons.load(1, 0), w);
    Load("loadGameButton",          mainMenuButtons.load(0, 1), w);
    Load("loadGameButtonSelected",  mainMenuButtons.load(1, 1), w);
    Load("settingsButton",          mainMenuButtons.load(0, 2), w);
    Load("settingsButtonSelected",  mainMenuButtons.load(1, 2), w);
    Load("exitButton",              mainMenuButtons.load(0, 3), w);
    Load("exitButtonSelected",      mainMenuButtons.load(1, 3), w);
    Load("backButton",              mainMenuButtons.load(0, 4), w);
    Load("backButtonSelected",      mainMenuButtons.load(1, 4), w);
    Load("showFPS",                 mainMenuButtons.load(0, 5), w);
    Load("showFPSSelected",         mainMenuButtons.load(1, 5), w);
    Load("hideFPS",                 mainMenuButtons.load(0, 6), w);
    Load("hideFPSSelected",         mainMenuButtons.load(1, 6), w);
    Load("30FPS",                   mainMenuButtons.load(2, 0), w);
    Load("30FPSSelected",           mainMenuButtons.load(3, 0), w);
    Load("60FPS",                   mainMenuButtons.load(2, 1), w);
    Load("60FPSSelected",           mainMenuButtons.load(3, 1), w);
    Load("uncappedFPS",             mainMenuButtons.load(2, 2), w);
    Load("uncappedFPSSelected",     mainMenuButtons.load(3, 2), w);
    Load("slotFull",                mainMenuButtons.load(2, 3), w);
    Load("slotFullSelected",        mainMenuButtons.load(3, 3), w);
    Load("slotEmpty",               mainMenuButtons.load(2, 4), w);
    Load("slotEmptySelected",       mainMenuButtons.load(3, 4), w);
    Load("menuConfirm",             mainMenuButtons.load(2, 5), w);
    Load("menuConfirmSelected",     mainMenuButtons.load(3, 5), w);
    Load("menuCancel",              mainMenuButtons.load(2, 6), w);
    Load("menuCancelSelected",      mainMenuButtons.load(3, 6), w);

    SpriteSheet xButton("res/textures/XButton.png", 50, 50);
    Load("xButton",                     xButton.load(0, 0), w);
    Load("xButtonSelected",             xButton.load(1, 0), w);

    SpriteSheet baseButtons("res/textures/BaseButtons.png", 180, 50);
    Load("confirmButton",               baseButtons.load(0, 0), w);
    Load("confirmButtonSelected",       baseButtons.load(1, 0), w);
    Load("cancelButton",                baseButtons.load(2, 0), w);
    Load("cancelButtonSelected",        baseButtons.load(3, 0), w);
    Load("nextDayButton",               baseButtons.load(0, 1), w);
    Load("nextDayButtonSelected",       baseButtons.load(1, 1), w);
    Load("restButton",                  baseButtons.load(2, 1), w);
    Load("restButtonSelected",          baseButtons.load(3, 1), w);
    Load("getResourcesButton",          baseButtons.load(0, 2), w);
    Load("getResourcesButtonSelected",  baseButtons.load(1, 2), w);
    Load("goFishingButton",             baseButtons.load(2, 2), w);
    Load("goFishingButtonSelected",     baseButtons.load(3, 2), w);
    Load("visitLibraryButton",          baseButtons.load(0, 3), w);
    Load("visitLibraryButtonSelected",  baseButtons.load(1, 3), w);
    Load("smithButton",                 baseButtons.load(2, 3), w);
    Load("smithButtonSelected",         baseButtons.load(3, 3), w);
    Load("goTavernButton",              baseButtons.load(0, 4), w);
    Load("goTavernButtonSelected",      baseButtons.load(1, 4), w);
    Load("beginCombatButton",           baseButtons.load(2, 4), w);
    Load("beginCombatButtonSelected",   baseButtons.load(3, 4), w);
    Load("returnToCampButton",          baseButtons.load(0, 5), w);
    Load("returnToCampButtonSelected",  baseButtons.load(1, 5), w);
    Load("prayButton",                  baseButtons.load(2, 5), w);
    Load("prayButtonSelected",          baseButtons.load(3, 5), w);
    Load("buildButton",                 baseButtons.load(0, 6), w);
    Load("buildButtonSelected",         baseButtons.load(1, 6), w);
    Load("exploreButton",               baseButtons.load(2, 6), w);
    Load("exploreButtonSelected",       baseButtons.load(3, 6), w);
    Load("mineButton",                  baseButtons.load(0, 7), w);
    Load("mineButtonSelected",          baseButtons.load(1, 7), w);
    Load("chopWoodButton",              baseButtons.load(2, 7), w);
    Load("chopWoodButtonSelected",      baseButtons.load(3, 7), w);
    Load("farmButton",                  baseButtons.load(0, 8), w);
    Load("farmButtonSelected",          baseButtons.load(1, 8), w);
    Load("backToMenuButton",            baseButtons.load(2, 8), w);
    Load("backToMenuButtonSelected",    baseButtons.load(3, 8), w);
    Load("tradeButton",                 baseButtons.load(0, 9), w);
    Load("tradeButtonSelected",         baseButtons.load(1, 9), w);
    Load("manageWorkersButton",         baseButtons.load(2, 9), w);
    Load("manageWorkersButtonSelected", baseButtons.load(3, 9), w);
    Load("continueButton",              baseButtons.load(0, 10), w);
    Load("continueButtonSelected",      baseButtons.load(1, 10), w);
    Load("joustButton",                 baseButtons.load(2, 10), w);
    Load("joustButtonSelected",         baseButtons.load(3, 10), w);
    Load("studyButton",                 baseButtons.load(0, 11), w);
    Load("studyButtonSelected",         baseButtons.load(1, 11), w);
    Load("archeryButton",               baseButtons.load(2, 11), w);
    Load("archeryButtonSelected",       baseButtons.load(3, 11), w);
    Load("meditateButton",              baseButtons.load(0, 12), w);
    Load("meditateButtonSelected",      baseButtons.load(1, 12), w);
    Load("experimentButton",            baseButtons.load(2, 12), w);
    Load("experimentButtonSelected",    baseButtons.load(3, 12), w);
    Load("composeButton",               baseButtons.load(0, 13), w);
    Load("composeButtonSelected",       baseButtons.load(1, 13), w);
        
    SpriteSheet buildHireButtons("res/textures/BuildHireButtons.png", 128, 50);
    Load("buildHouseButton",            buildHireButtons.load(0, 0), w);
    Load("buildHouseButtonSelected",    buildHireButtons.load(1, 0), w);
    Load("hireWorkerButton",            buildHireButtons.load(0, 1), w);
    Load("hireWorkerButtonSelected",    buildHireButtons.load(1, 1), w);

    SpriteSheet buildButtons("res/textures/BuildButtons.png", 375, 65);
    Load("buildBed",                        buildButtons.load(0, 0), w);
    Load("buildHouse",                      buildButtons.load(0, 1), w);
    Load("buildLibrary",                    buildButtons.load(0, 2), w);
    Load("buildTrader",                     buildButtons.load(0, 3), w);
    Load("buildFishery",                    buildButtons.load(0, 4), w);
    Load("buildChapel",                     buildButtons.load(0, 5), w);
    Load("buildSmithy",                     buildButtons.load(0, 6), w);
    Load("buildTavern",                     buildButtons.load(0, 7), w);
    Load("buildMagicalGenerator",           buildButtons.load(0, 8), w);
    Load("buildArcheryRange",               buildButtons.load(0, 9), w);
    Load("buildWizardTower",                buildButtons.load(0, 10), w);
    Load("buildTemple",                     buildButtons.load(0, 11), w);
    Load("buildAlchemyLab",                 buildButtons.load(0, 12), w);
    Load("buildMusicHall",                  buildButtons.load(0, 13), w);
    Load("buildBedSelected",                buildButtons.load(1, 0), w);
    Load("buildHouseSelected",              buildButtons.load(1, 1), w);
    Load("buildLibrarySelected",            buildButtons.load(1, 2), w);
    Load("buildTraderSelected",             buildButtons.load(1, 3), w);
    Load("buildFisherySelected",            buildButtons.load(1, 4), w);
    Load("buildChapelSelected",             buildButtons.load(1, 5), w);
    Load("buildSmithySelected",             buildButtons.load(1, 6), w);
    Load("buildTavernSelected",             buildButtons.load(1, 7), w);
    Load("buildMagicalGeneratorSelected",   buildButtons.load(1, 8), w);
    Load("buildArcheryRangeSelected",       buildButtons.load(1, 9), w);
    Load("buildWizardTowerSelected",        buildButtons.load(1, 10), w);
    Load("buildTempleSelected",             buildButtons.load(1, 11), w);
    Load("buildAlchemyLabSelected",         buildButtons.load(1, 12), w);
    Load("buildMusicHallSelected",          buildButtons.load(1, 13), w);

    SpriteSheet combatButtons("res/textures/CombatButtons.png", 384, 128);
    Load("startButton",         combatButtons.load(0, 0), w);
    Load("startButtonSelected", combatButtons.load(1, 0), w);
    Load("pause",               combatButtons.load(2, 0), w);
    Load("pauseSelected",       combatButtons.load(3, 0), w);
    Load("endButton",           combatButtons.load(0, 1), w);
    Load("endButtonSelected",   combatButtons.load(1, 1), w);
    Load("speed1",              combatButtons.load(2, 1), w);
    Load("speed1Selected",      combatButtons.load(3, 1), w);
    Load("speed2",              combatButtons.load(0, 2), w);
    Load("speed2Selected",      combatButtons.load(1, 2), w);
    Load("speed3",              combatButtons.load(2, 2), w);
    Load("speed3Selected",      combatButtons.load(3, 2), w);

    SpriteSheet eventButtons("res/textures/EventButtons.png", 600, 50);
    Load("eventButton",         eventButtons.load(0, 0), w);
    Load("eventButtonSelected", eventButtons.load(0, 1), w);

    SpriteSheet combatRewardButton("res/textures/CombatRewardButton.png", 180, 50);
    Load("CombatReward",            combatRewardButton.load(0, 0), w);
    Load("CombatRewardSelected",    combatRewardButton.load(1, 0), w);

    SpriteSheet playerButtons("res/textures/PlayerButtons.png", 300, 300);
    Load("viewDeckButton",              playerButtons.load(0, 0), w);
    Load("viewDeckButtonSelected",      playerButtons.load(1, 0), w);
    Load("viewArtifactsButton",         playerButtons.load(0, 1), w);
    Load("viewArtifactsButtonSelected", playerButtons.load(1, 1), w);

    SpriteSheet tradeButtons("res/textures/TradeButtons.png", 200, 80);
    Load("buyWoodButton",           tradeButtons.load(0, 0), w);
    Load("buyStoneButton",          tradeButtons.load(0, 1), w);
    Load("buyWheatButton",          tradeButtons.load(0, 2), w);
    Load("spinButton",              tradeButtons.load(0, 3), w);
    Load("buyWoodButtonSelected",   tradeButtons.load(1, 0), w);
    Load("buyStoneButtonSelected",  tradeButtons.load(1, 1), w);
    Load("buyWheatButtonSelected",  tradeButtons.load(1, 2), w);
    Load("spinButtonSelected",      tradeButtons.load(1, 3), w);

    SpriteSheet statIcons("res/textures/Stats.png", 64, 64);
    Load("healthIcon",              statIcons.load(0, 0), w);
    Load("goldIcon",                statIcons.load(1, 0), w);
    Load("energyIcon",              statIcons.load(2, 0), w);
    Load("woodIcon",                statIcons.load(3, 0), w);
    Load("stoneIcon",               statIcons.load(4, 0), w);
    Load("wheatIcon",               statIcons.load(5, 0), w);
    Load("workerIcon",              statIcons.load(6, 0), w);
    Load("houseIcon",               statIcons.load(0, 1), w);
    Load("settingsIcon",            statIcons.load(1, 1), w);
    Load("settingsIconSelected",    statIcons.load(2, 1), w);
    
    SpriteSheet auras("res/textures/auras.png", 64, 64);
    Load("lifeSteal",           auras.load(0, 0), w);
    Load("poisonWeapons",       auras.load(1, 0), w);
    Load("stunAttacks",         auras.load(2, 0), w);
    Load("constantDamage",      auras.load(3, 0), w);
    Load("deathExplosions",     auras.load(4, 0), w);
    Load("storm",               auras.load(5, 0), w);
    Load("enhancePoison",       auras.load(6, 0), w);
    Load("damageUp",            auras.load(7, 0), w);
    Load("multiShot",           auras.load(0, 1), w);
    Load("critChance",          auras.load(1, 1), w);
    Load("critDamage",          auras.load(2, 1), w);
    Load("sight",               auras.load(3, 1), w);
    Load("focusUp",             auras.load(4, 1), w);

    SpriteSheet plusMinus("res/textures/PlusMinus.png", 64, 64);
    Load("plus",            plusMinus.load(0, 0), w);
    Load("plusSelected",    plusMinus.load(1, 0), w);
    Load("minus",           plusMinus.load(0, 1), w);
    Load("minusSelected",   plusMinus.load(1, 1), w);

    SpriteSheet doublePlusDoubleMinus("res/textures/DoublePlusDoubleMinus.png", 94, 70);
    Load("addAll",              doublePlusDoubleMinus.load(0, 0), w);
    Load("addAllSelected",      doublePlusDoubleMinus.load(1, 0), w);
    Load("minusAll",            doublePlusDoubleMinus.load(0, 1), w);
    Load("minusAllSelected",    doublePlusDoubleMinus.load(1, 1), w);

    SpriteSheet upgradeButton("res/textures/UpgradeButton.png", 132, 40);
    Load("upgradeButton", upgradeButton.load(0, 0), w);
    Load("upgradeButtonSelected", upgradeButton.load(0, 1), w);

    SpriteSheet towerUpgrades("res/textures/Upgrades.png", 50, 50);
    Load("damageUpgrade",                   towerUpgrades.load(0, 0), w);
    Load("damageUpgradeSelected",           towerUpgrades.load(0, 1), w);
    Load("rangeUpgrade",                    towerUpgrades.load(1, 0), w);
    Load("rangeUpgradeSelected",            towerUpgrades.load(1, 1), w);
    Load("attackSpeedUpgrade",              towerUpgrades.load(2, 0), w);
    Load("attackSpeedUpgradeSelected",      towerUpgrades.load(2, 1), w);
    Load("moreMissilesUpgrade",             towerUpgrades.load(3, 0), w);
    Load("moreMissilesUpgradeSelected",     towerUpgrades.load(3, 1), w);
    Load("critUpgrade",                     towerUpgrades.load(4, 0), w);
    Load("critUpgradeSelected",             towerUpgrades.load(4, 1), w);
    Load("armorPenUpgrade",                 towerUpgrades.load(5, 0), w);
    Load("armorPenUpgradeSelected",         towerUpgrades.load(5, 1), w);
    Load("multishotUpgrade",                towerUpgrades.load(6, 0), w);
    Load("multishotUpgradeSelected",        towerUpgrades.load(6, 1), w);
    Load("moreFocusUpgrade",                towerUpgrades.load(7, 0), w);
    Load("moreFocusUpgradeSelected",        towerUpgrades.load(7, 1), w);
    Load("heightenedSensesUpgrade",         towerUpgrades.load(8, 0), w);
    Load("heightenedSensesUpgradeSelected", towerUpgrades.load(8, 1), w);
    Load("elementalistUpgrade",             towerUpgrades.load(0, 2), w);
    Load("elementalistUpgradeSelected",     towerUpgrades.load(0, 3), w);
    Load("conjurerUpgrade",                 towerUpgrades.load(1, 2), w);
    Load("conjurerUpgradeSelected",         towerUpgrades.load(1, 3), w);
    Load("necromancerUpgrade",              towerUpgrades.load(2, 2), w);
    Load("necromancerUpgradeSelected",      towerUpgrades.load(2, 3), w);
    Load("crossbowmanUpgrade",              towerUpgrades.load(3, 2), w);
    Load("crossbowmanUpgradeSelected",      towerUpgrades.load(3, 3), w);
    Load("greyEyesUpgrade",                 towerUpgrades.load(4, 2), w);
    Load("greyEyesUpgradeSelected",         towerUpgrades.load(4, 3), w);
    Load("bbGunnerUpgrade",                 towerUpgrades.load(5, 2), w);
    Load("bbGunnerUpgradeSelected",         towerUpgrades.load(5, 3), w);
    Load("animalCompanionUpgrade",          towerUpgrades.load(6, 2), w);
    Load("animalCompanionUpgradeSelected",  towerUpgrades.load(6, 3), w);
    Load("sniperUpgrade",                   towerUpgrades.load(7, 2), w);
    Load("sniperUpgradeSelected",           towerUpgrades.load(7, 3), w);
    Load("laserBowUpgrade",                 towerUpgrades.load(8, 2), w);
    Load("laserBowUpgradeSelected",         towerUpgrades.load(8, 3), w);
    Load("wingsUpgrade",                    towerUpgrades.load(0, 4), w);
    Load("wingsUpgradeSelected",            towerUpgrades.load(0, 5), w);
    Load("vengenceUpgrade",                 towerUpgrades.load(1, 4), w);
    Load("vengenceUpgradeSelected",         towerUpgrades.load(1, 5), w);
    Load("inspiringLeaderUpgrade",          towerUpgrades.load(2, 4), w);
    Load("inspiringLeaderUpgradeSelected",  towerUpgrades.load(2, 5), w);
    Load("grenadeGunnerUpgrade",            towerUpgrades.load(3, 4), w);
    Load("grenadeGunnerUpgradeSelected",    towerUpgrades.load(3, 5), w);
    Load("trueAlchemyUpgrade",              towerUpgrades.load(4, 4), w);
    Load("trueAlchemyUpgradeSelected",      towerUpgrades.load(4, 5), w);
    Load("poisonerUpgrade",                 towerUpgrades.load(5, 4), w);
    Load("poisonerUpgradeSelected",         towerUpgrades.load(5, 5), w);
    Load("pacifistUpgrade",                 towerUpgrades.load(6, 4), w);
    Load("pacifistUpgradeSelected",         towerUpgrades.load(6, 5), w);
    Load("empowererUpgrade",                towerUpgrades.load(7, 4), w);
    Load("empowererUpgradeSelected",        towerUpgrades.load(7, 5), w);
    Load("disarmingWordsUpgrade",           towerUpgrades.load(8, 4), w);
    Load("disarmingWordsUpgradeSelected",   towerUpgrades.load(8, 5), w);
    Load("lifebringerUpgrade",              towerUpgrades.load(0, 6), w);
    Load("lifebringerUpgradeSelected",      towerUpgrades.load(0, 7), w);
    Load("battleClericUpgrade",             towerUpgrades.load(1, 6), w);
    Load("battleClericUpgradeSelected",     towerUpgrades.load(1, 7), w);
    Load("deathPriestUpgrade",              towerUpgrades.load(2, 6), w);
    Load("deathPriestUpgradeSelected",      towerUpgrades.load(2, 7), w);

    SpriteSheet skillTreeSkills("res/textures/SkillTreeSkills.png", 64, 64);
    Load("DamageSkill1",                    skillTreeSkills.load(0, 0), w);
    Load("DamageSkill1Selected",            skillTreeSkills.load(1, 0), w);
    Load("DamageSkill2",                    skillTreeSkills.load(0, 1), w);
    Load("DamageSkill2Selected",            skillTreeSkills.load(1, 1), w);
    Load("DamageSkill3",                    skillTreeSkills.load(0, 2), w);
    Load("DamageSkill3Selected",            skillTreeSkills.load(1, 2), w);
    Load("CritChanceSkill1",                skillTreeSkills.load(2, 0), w);
    Load("CritChanceSkill1Selected",        skillTreeSkills.load(3, 0), w);
    Load("CritChanceSkill2",                skillTreeSkills.load(2, 1), w);
    Load("CritChanceSkill2Selected",        skillTreeSkills.load(3, 1), w);
    Load("CritChanceSkill3",                skillTreeSkills.load(2, 2), w);
    Load("CritChanceSkill3Selected",        skillTreeSkills.load(3, 2), w);
    Load("CritDamageSkill1",                skillTreeSkills.load(4, 0), w);
    Load("CritDamageSkill1Selected",        skillTreeSkills.load(5, 0), w);
    Load("CritDamageSkill2",                skillTreeSkills.load(4, 1), w);
    Load("CritDamageSkill2Selected",        skillTreeSkills.load(5, 1), w);
    Load("CritDamageSkill3",                skillTreeSkills.load(4, 2), w);
    Load("CritDamageSkill3Selected",        skillTreeSkills.load(5, 2), w);
    Load("MultiShotSkill1",                 skillTreeSkills.load(0, 3), w);
    Load("MultiShotSkill1Selected",         skillTreeSkills.load(1, 3), w);
    Load("MultiShotSkill2",                 skillTreeSkills.load(0, 4), w);
    Load("MultiShotSkill2Selected",         skillTreeSkills.load(1, 4), w);
    Load("FocusSkill1",                     skillTreeSkills.load(2, 3), w);
    Load("FocusSkill1Selected",             skillTreeSkills.load(3, 3), w);
    Load("FocusSkill2",                     skillTreeSkills.load(2, 4), w);
    Load("FocusSkill2Selected",             skillTreeSkills.load(3, 4), w);
    Load("Level10Skill",                    skillTreeSkills.load(6, 0), w);
    Load("Level10SkillSelected",            skillTreeSkills.load(7, 0), w);

    loadCategory = "Towers";
    
    SpriteSheet towers("res/textures/Towers.png", 64, 64);
    Load("Archer",                      towers.load(0, 0), w);
    Load("ArcherHighlighted",           towers.load(1, 0), w);
    Load("Crossbowman",                 towers.load(2, 0), w);
    Load("CrossbowmanHighlighted",      towers.load(3, 0), w);
    Load("GreyEyes",                    towers.load(4, 0), w);
    Load("GreyEyesHighlighted",         towers.load(5, 0), w);
    Load("BBGunner",                    towers.load(6, 0), w);
    Load("BBGunnerHighlighted",         towers.load(7, 0), w);
    Load("Ranger",                      towers.load(0, 1), w);
    Load("RangerHighlighted",           towers.load(1, 1), w);
    Load("AnimalCompanion",             towers.load(2, 1), w);
    Load("AnimalCompanionHighlighted",  towers.load(3, 1), w);
    Load("Sniper",                      towers.load(4, 1), w);
    Load("SniperHighlighted",           towers.load(5, 1), w);
    Load("LaserBow",                    towers.load(6, 1), w);
    Load("LaserBowHighlighted",         towers.load(7, 1), w);
    Load("Wizard",                      towers.load(0, 2), w);
    Load("WizardHighlighted",           towers.load(1, 2), w);
    Load("Elementalist",                towers.load(2, 2), w);
    Load("ElementalistHighlighted",     towers.load(3, 2), w);
    Load("Conjurer",                    towers.load(4, 2), w);
    Load("ConjurerHighlighted",         towers.load(5, 2), w);
    Load("Necromancer",                 towers.load(6, 2), w);
    Load("NecromancerHighlighted",      towers.load(7, 2), w);
    Load("Alchemist",                   towers.load(0, 3), w);
    Load("AlchemistHighlighted",        towers.load(1, 3), w);
    Load("GrenadeGunner",               towers.load(2, 3), w);
    Load("GrenadeGunnerHighlighted",    towers.load(3, 3), w);
    Load("TrueAlchemist",               towers.load(4, 3), w);
    Load("TrueAlchemistHighlighted",    towers.load(5, 3), w);
    Load("Poisoner",                    towers.load(6, 3), w);
    Load("PoisonerHighlighted",         towers.load(7, 3), w);
    Load("Paladin",                     towers.load(0, 4), w);
    Load("PaladinHighlighted",          towers.load(1, 4), w);
    Load("WingedPaladin",               towers.load(2, 4), w);
    Load("WingedPaladinHighlighted",    towers.load(3, 4), w);
    Load("VengencePaladin",             towers.load(4, 4), w);
    Load("VengencePaladinHighlighted",  towers.load(5, 4), w);
    Load("InspiringPaladin",            towers.load(6, 4), w);
    Load("InspiringPaladinHighlighted", towers.load(7, 4), w);
    Load("GIANT",                       towers.load(0, 5), w);
    Load("GIANTHighlighted",            towers.load(1, 5), w);
    Load("Bard",                        towers.load(0, 6), w);
    Load("BardHighlighted",             towers.load(1, 6), w);
    Load("PeaceBard",                   towers.load(2, 6), w);
    Load("PeaceBardHighlighted",        towers.load(3, 6), w);
    Load("Empowerer",                   towers.load(4, 6), w);
    Load("EmpowererHighlighted",        towers.load(5, 6), w);
    Load("DisarmingBard",               towers.load(6, 6), w);
    Load("DisarmingBardHighlighted",    towers.load(7, 6), w);
    Load("Cleric",                      towers.load(0, 7), w);
    Load("ClericHighlighted",           towers.load(1, 7), w);
    Load("LifebringerCleric",           towers.load(2, 7), w);
    Load("LifebringerClericHighlighted",towers.load(3, 7), w);
    Load("BattleCleric",                towers.load(4, 7), w);
    Load("BattleClericHighlighted",     towers.load(5, 7), w);
    Load("DeathPriest",                 towers.load(6, 7), w);
    Load("DeathPriestHighlighted",      towers.load(7, 7), w);
    Load("Scholar",                     towers.load(0, 8), w);
    Load("ScholarHighlighted",          towers.load(1, 8), w);
    Load("Falcon",                      towers.load(0, 9), w);
    Load("FalconHighlighted",           towers.load(1, 9), w);
    Load("ScholarSelected",             towers.load(2, 9), w);

    loadCategory = "Enemies";

    SpriteSheet enemies("res/textures/Enemies.png", 64, 64);
    Load("Rat",                     enemies.load(0, 0), w);
    Load("RatSelected",             enemies.load(1, 0), w);
    Load("Giant Rat",               enemies.load(2, 0), w);
    Load("Giant RatSelected",       enemies.load(3, 0), w);
    Load("Boss Rat",                enemies.load(4, 0), w);
    Load("Boss RatSelected",        enemies.load(5, 0), w);
    Load("Shield Rat",              enemies.load(6, 0), w);
    Load("Shield RatSelected",      enemies.load(7, 0), w);
    Load("ShieldlessRat",           enemies.load(8, 0), w);
    Load("ShieldlessRatSelected",   enemies.load(9, 0), w);
    Load("Shaman Rat",              enemies.load(10, 0), w);
    Load("Shaman RatSelected",      enemies.load(11, 0), w);
    Load("Healer Rat",              enemies.load(10, 0), w);
    Load("Healer RatSelected",      enemies.load(11, 0), w);
    Load("Witch Rat",               enemies.load(10, 0), w);
    Load("Witch RatSelected",       enemies.load(11, 0), w);
    Load("Plague Rat",              enemies.load(12, 0), w);
    Load("Plague RatSelected",      enemies.load(13, 0), w);
    Load("Assassin Rat",            enemies.load(14, 0), w);
    Load("Assassin RatSelected",    enemies.load(15, 0), w);

    Load("Slime",                   enemies.load(0, 2), w);
    Load("SlimeSelected",           enemies.load(1, 2), w);
    Load("Blob",                    enemies.load(2, 2), w);
    Load("BlobSelected",            enemies.load(3, 2), w);
    Load("Ooze",                    enemies.load(4, 2), w);
    Load("OozeSelected",            enemies.load(5, 2), w);
    Load("Double Ooze",             enemies.load(6, 2), w);
    Load("Double OozeSelected",     enemies.load(7, 2), w);
    Load("Mega Ooze",               enemies.load(8, 2), w);
    Load("Mega OozeSelected",       enemies.load(9, 2), w);
    Load("Jumping Ooze",            enemies.load(10, 2), w);
    Load("Jumping OozeSelected",    enemies.load(11, 2), w);
    Load("Toxic Slime",             enemies.load(12, 2), w);
    Load("Toxic SlimeSelected",     enemies.load(13, 2), w);
    Load("Doubler",                 enemies.load(14, 2), w);
    Load("DoublerSelected",         enemies.load(15, 2), w);
    Load("Writhing Mass",           enemies.load(0, 3), w);
    Load("Writhing MassSelected",   enemies.load(1, 3), w);

    Load("Beetle",                  enemies.load(0, 4), w);
    Load("BeetleSelected",          enemies.load(1, 4), w);
    Load("Spider",                  enemies.load(2, 4), w);
    Load("SpiderSelected",          enemies.load(3, 4), w);
    Load("Tough Beetle",            enemies.load(4, 4), w);
    Load("Tough BeetleSelected",    enemies.load(5, 4), w);
    Load("Blink Bug",               enemies.load(6, 4), w);
    Load("Blink BugSelected",       enemies.load(7, 4), w);
    Load("Runner Beetle",           enemies.load(8, 4), w);
    Load("Runner BeetleSelected",   enemies.load(9, 4), w);
    Load("Tank Beetle",             enemies.load(10, 4), w);
    Load("Tank BeetleSelected",     enemies.load(11, 4), w);
    Load("Gnat",                    enemies.load(12, 4), w);
    Load("GnatSelected",            enemies.load(13, 4), w);
    Load("Ankheg",                  enemies.load(0, 5), w);
    Load("AnkhegSelected",          enemies.load(1, 5), w);
    Load("Fire Fly",                enemies.load(2, 5), w);
    Load("Fire FlySelected",        enemies.load(3, 5), w);

    Load("Goblin",                  enemies.load(0, 6), w);
    Load("GoblinSelected",          enemies.load(1, 6), w);
    Load("Orc ",                    enemies.load(2, 6), w);
    Load("Orc Selected",            enemies.load(3, 6), w);

    loadCategory = "Cards";

    SpriteSheet towerCards("res/textures/TowerCards.png", 440, 560);
    Load("archerCard",              towerCards.load(0, 0), w);
    Load("archerCardUpgraded",      towerCards.load(1, 0), w);
    Load("wizardCard",              towerCards.load(2, 0), w);
    Load("wizardCardUpgraded",      towerCards.load(3, 0), w);
    Load("alchemistCard",           towerCards.load(4, 0), w);
    Load("alchemistCardUpgraded",   towerCards.load(5, 0), w);
    Load("bardCard",                towerCards.load(0, 1), w);
    Load("bardCardUpgraded",        towerCards.load(1, 1), w);
    Load("clericCard",              towerCards.load(2, 1), w);
    Load("clericCardUpgraded",      towerCards.load(3, 1), w);
    Load("paladinCard",             towerCards.load(4, 1), w);
    Load("paladinCardUpgraded",     towerCards.load(5, 1), w);
    Load("giantCard",               towerCards.load(0, 2), w);
    Load("giantCardUpgraded",       towerCards.load(1, 2), w);
    Load("scholarCard",             towerCards.load(2, 2), w);
    Load("scholarCardUpgraded",     towerCards.load(3, 2), w);
    Load("rangerCard",              towerCards.load(4, 2), w);
    Load("rangerCardUpgraded",      towerCards.load(5, 2), w);

    SpriteSheet skillCards("res/textures/SkillCards.png", 440, 560);
    Load("focus",                   skillCards.load(0, 0), w);
    Load("focusUpgraded",           skillCards.load(1, 0), w);
    Load("focusExhausts",           skillCards.load(2, 0), w);
    Load("focusExhaustsUpgraded",   skillCards.load(3, 0), w);
    Load("potOfGreed",              skillCards.load(4, 0), w);
    Load("potOfGreedUpgraded",      skillCards.load(5, 0), w);
    Load("study",                   skillCards.load(6, 0), w);
    Load("studyUpgraded",           skillCards.load(7, 0), w);

    Load("center",                  skillCards.load(0, 1), w);
    Load("centerUpgraded",          skillCards.load(1, 1), w);
    Load("double",                  skillCards.load(2, 1), w);
    Load("doubleUpgraded",          skillCards.load(3, 1), w);

    Load("sift",                    skillCards.load(0, 2), w);
    Load("siftUpgraded",            skillCards.load(1, 2), w);
    Load("reflect",                 skillCards.load(2, 2), w);
    Load("reflectUpgraded",         skillCards.load(3, 2), w);
    Load("skim",                    skillCards.load(4, 2), w);
    Load("skimUpgraded",            skillCards.load(5, 2), w);
    Load("refresh",                 skillCards.load(6, 2), w);
    Load("refreshUpgraded",         skillCards.load(7, 2), w);

    Load("fireBall",                skillCards.load(0, 3), w);
    Load("fireBallUpgraded",        skillCards.load(1, 3), w);
    Load("frostBall",               skillCards.load(2, 3), w);
    Load("frostBallUpgraded",       skillCards.load(3, 3), w);
    Load("lightning",               skillCards.load(4, 3), w);
    Load("lightningUpgraded",       skillCards.load(5, 3), w);
    Load("poisonBall",              skillCards.load(6, 3), w);
    Load("poisonBallUpgraded",      skillCards.load(7, 3), w);

    Load("gather",                  skillCards.load(0, 4), w);
    Load("gatherUpgraded",          skillCards.load(1, 4), w);
    Load("concentrate",             skillCards.load(2, 4), w);
    Load("concentrateUpgraded",     skillCards.load(3, 4), w);
    Load("recharge",                skillCards.load(4, 4), w);
    Load("rechargeUpgraded",        skillCards.load(5, 4), w);
    Load("attain",                  skillCards.load(6, 4), w);
    Load("attainUpgraded",          skillCards.load(7, 4), w);
    
    Load("ren",                     skillCards.load(0, 5), w);
    Load("renUpgraded",             skillCards.load(1, 5), w);
    Load("surge",                   skillCards.load(2, 5), w);
    Load("surgeUpgraded",           skillCards.load(3, 5), w);
    Load("massStun",                skillCards.load(4, 5), w);
    Load("massStunUpgraded",        skillCards.load(5, 5), w);

    SpriteSheet auraCards("res/textures/AuraCards.png", 440, 560);
    Load("lifeAura",                    auraCards.load(0, 0), w);
    Load("lifeAuraUpgraded",            auraCards.load(1, 0), w);
    Load("envenom",                     auraCards.load(2, 0), w);
    Load("envenomUpgraded",             auraCards.load(3, 0), w);
    Load("stunningStrikes",             auraCards.load(4, 0), w);
    Load("stunningStrikesUpgraded",     auraCards.load(5, 0), w);
    Load("theFloorIsLava",              auraCards.load(6, 0), w);
    Load("theFloorIsLavaUpgraded",      auraCards.load(7, 0), w);
    Load("strongPoisons",               auraCards.load(0, 1), w);
    Load("strongPoisonsUpgraded",       auraCards.load(1, 1), w);
    Load("echoLocation",                auraCards.load(2, 1), w);
    Load("echoLocationUpgraded",        auraCards.load(3, 1), w);
    Load("explosiveStrikes",            auraCards.load(4, 1), w);
    Load("explosiveStrikesUpgraded",    auraCards.load(5, 1), w);
    Load("lightningStorm",              auraCards.load(6, 1), w);
    Load("lightningStormUpgraded",      auraCards.load(7, 1), w);

    SpriteSheet curses("res/textures/Curses.png", 440, 560);
    Load("Flames",              curses.load(0, 0), w);
    Load("FlamesUpgraded",      curses.load(1, 0), w);
    Load("Frog",                curses.load(2, 0), w);
    Load("FrogUpgraded",        curses.load(3, 0), w);
    Load("Infection",           curses.load(4, 0), w);
    Load("InfectionUpgraded",   curses.load(5, 0), w);
    Load("Hex",                 curses.load(6, 0), w);
    Load("HexUpgraded",         curses.load(7, 0), w);
    Load("Sludge",              curses.load(0, 1), w);
    Load("SludgeUpgraded",      curses.load(1, 1), w);

    SpriteSheet cardInfo("res/textures/InfoTiles.png", 440, 170);
    Load("SummonInfo",      cardInfo.load(0, 0), w);
    Load("UpgradedInfo",    cardInfo.load(1, 0), w);
    Load("Human",           cardInfo.load(2, 0), w);
    Load("Dwarf",           cardInfo.load(3, 0), w);
    Load("High Elf",        cardInfo.load(0, 1), w);
    Load("Wood Elf",        cardInfo.load(1, 1), w);
    Load("Gnome",           cardInfo.load(2, 1), w);
    Load("Orc",             cardInfo.load(3, 1), w);
    Load("Giant",           cardInfo.load(0, 2), w);
    Load("Explorer",        cardInfo.load(1, 2), w);
    Load("Battle Ready",    cardInfo.load(2, 2), w);
    Load("Veteran",         cardInfo.load(3, 2), w);
    Load("Just Lucky",      cardInfo.load(0, 3), w);
    Load("Farsighted",      cardInfo.load(1, 3), w);
    Load("Nearsighted",     cardInfo.load(2, 3), w);
    Load("exhaustInfo",     cardInfo.load(3, 3), w);
    Load("poisonInfo",      cardInfo.load(0, 4), w);
    Load("auraInfo",        cardInfo.load(1, 4), w);
    Load("stunInfo",        cardInfo.load(2, 4), w);
    Load("slowInfo",        cardInfo.load(3, 4), w);
    Load("Spellweaver",     cardInfo.load(0, 5), w);
    Load("Sage",            cardInfo.load(1, 5), w);
    Load("Fighter",         cardInfo.load(2, 5), w);
    Load("Berserker",       cardInfo.load(3, 5), w);
    Load("Super Senses",    cardInfo.load(0, 6), w);

    SpriteSheet heroImages("res/textures/HeroImages.png", 440, 560);
    Load("humanMale",       heroImages.load(0, 0), w);
    Load("humanFemale",     heroImages.load(1, 0), w);
    Load("dwarfMale",       heroImages.load(2, 0), w);
    Load("dwarfFemale",     heroImages.load(3, 0), w);
    Load("highElfMale",     heroImages.load(4, 0), w);
    Load("highElfFemale",   heroImages.load(5, 0), w);
    Load("woodElfMale",     heroImages.load(0, 1), w);
    Load("woodElfFemale",   heroImages.load(1, 1), w);
    Load("gnomeMale",       heroImages.load(2, 1), w);
    Load("gnomeFemale",     heroImages.load(3, 1), w);
    Load("orcMale",         heroImages.load(4, 1), w);
    Load("orcFemale",       heroImages.load(5, 1), w);
    Load("giantMale",       heroImages.load(0, 2), w);
    Load("giantFemale",     heroImages.load(1, 2), w);
    Load("heath",           heroImages.load(2, 2), w);
    Load("hoid",            heroImages.load(3, 2), w);
    Load("aramis",          heroImages.load(4, 2), w);

    SpriteSheet heroUpgrades("res/textures/HeroUpgrades.png", 440, 560);
    Load("damageUpgrade",       heroUpgrades.load(0, 0), w);
    Load("rangeUpgrade",        heroUpgrades.load(1, 0), w);
    Load("attackSpeedUpgrade",  heroUpgrades.load(2, 0), w);
    Load("moremissiles",        heroUpgrades.load(3, 0), w);

    loadCategory = "Artifacts";

    SpriteSheet artifacts("res/textures/Artifacts.png", 256, 256);
    Load("Token Of The Mute",       artifacts.load(0, 0), w);
    Load("Token Of The Armored",    artifacts.load(1, 0), w);
    Load("Token Of The Broken",     artifacts.load(2, 0), w);
    Load("Token Of The Vigilant",   artifacts.load(3, 0), w);
    Load("Blessing of the Bat",     artifacts.load(4, 0), w);
    Load("Lucky Axe",               artifacts.load(5, 0), w);
    Load("Lucky Pickaxe",           artifacts.load(6, 0), w);
    Load("Lucky Sythe",             artifacts.load(7, 0), w);
    Load("Boulder",                 artifacts.load(8, 0), w);
    Load("Magic Beans",             artifacts.load(9, 0), w);
    Load("Fruit Cake",              artifacts.load(0, 1), w);
    Load("Doll House",              artifacts.load(1, 1), w);
    Load("Toy Dolls",               artifacts.load(2, 1), w);
    Load("Hand of Midas",           artifacts.load(3, 1), w);
    Load("House Expansion Kit",     artifacts.load(4, 1), w);
    Load("Thermos",                 artifacts.load(5, 1), w);
    Load("Cooler",                  artifacts.load(6, 1), w);
    Load("Miniature Worm Hole",     artifacts.load(7, 1), w);
    Load("Special Toxins",          artifacts.load(8, 1), w);
    Load("Extra Slot",              artifacts.load(9, 1), w);
    Load("Prince",                  artifacts.load(0, 2), w);
    Load("Shrubbery",               artifacts.load(1, 2), w);
    Load("Blessed Hand Grenade",    artifacts.load(2, 2), w);
    Load("Explorers Hat",           artifacts.load(3, 2), w);
    Load("Map To Eldorado",         artifacts.load(4, 2), w);
    Load("Magical Generator",       artifacts.load(5, 2), w);

    SpriteSheet artifactInfo("res/textures/ArtifactInfo.png", 440, 170);
    Load("Token Of The MuteInfo",       artifactInfo.load(0, 0), w);
    Load("Token Of The ArmoredInfo",    artifactInfo.load(1, 0), w);
    Load("Token Of The BrokenInfo",     artifactInfo.load(2, 0), w);
    Load("Token Of The VigilantInfo",   artifactInfo.load(3, 0), w);
    Load("Blessing of the BatInfo",     artifactInfo.load(0, 1), w);
    Load("Lucky AxeInfo",               artifactInfo.load(1, 1), w);
    Load("Lucky PickaxeInfo",           artifactInfo.load(2, 1), w);
    Load("Lucky SytheInfo",             artifactInfo.load(3, 1), w);
    Load("BoulderInfo",                 artifactInfo.load(0, 2), w);
    Load("Magic BeansInfo",             artifactInfo.load(1, 2), w);
    Load("Fruit CakeInfo",              artifactInfo.load(2, 2), w);
    Load("Doll HouseInfo",              artifactInfo.load(3, 2), w);
    Load("Toy DollsInfo",               artifactInfo.load(0, 3), w);
    Load("Hand of MidasInfo",           artifactInfo.load(1, 3), w);
    Load("House Expansion KitInfo",     artifactInfo.load(2, 3), w);
    Load("ThermosInfo",                 artifactInfo.load(3, 3), w);
    Load("CoolerInfo",                  artifactInfo.load(0, 4), w);
    Load("Miniature Worm HoleInfo",     artifactInfo.load(1, 4), w);
    Load("Special ToxinsInfo",          artifactInfo.load(2, 4), w);
    Load("Extra SlotInfo",              artifactInfo.load(3, 4), w);
    Load("PrinceInfo",                  artifactInfo.load(0, 5), w);
    Load("ShrubberyInfo",               artifactInfo.load(1, 5), w);
    Load("Blessed Hand GrenadeInfo",    artifactInfo.load(2, 5), w);
    Load("Explorers HatInfo",           artifactInfo.load(3, 5), w);
    Load("Map To EldoradoInfo",         artifactInfo.load(0, 6), w);
    Load("Magical GeneratorInfo",       artifactInfo.load(1, 6), w);

    loadCategory = "Animations";

    SpriteSheet animationEffects("res/textures/AnimationEffects.png", 700, 100);
    Load("fireExplosion",       animationEffects.load(0, 0), w);
    Load("frostExplosion",      animationEffects.load(0, 1), w);
    Load("acidExplosion",       animationEffects.load(0, 2), w);
    Load("smiteAnimation",      animationEffects.load(0, 3), w);
    Load("critAnimation",       animationEffects.load(0, 4), w);
    Load("shamanAura",          animationEffects.load(0, 5), w);
    Load("healingAura",         animationEffects.load(0, 6), w);
}

void TowerDefense::LoadingScreen::Load(const std::string& path, std::shared_ptr<Texture> t, GLFWwindow* window)
{
    static int loadPercent = 0;
    static int numLoaded = 0;
    
    Texture::LoadTexture(path, t); //Cache texture
    numLoaded++;

    //Render loadbar and text if percent has changed
    int percent = (int)(((float)numLoaded / 578.0f) * 100.0f);
    if (loadPercent != percent)
    {
        RenderProgress(window, "Loading... " + loadCategory, percent);
        loadPercent = percent;
    }
}

//Renders loadbar, message, and load percent
void TowerDefense::LoadingScreen::RenderProgress(GLFWwindow* window, const std::string loadMessage, int loadPercent)
{
    Renderer::Get().Clear();

    Text loadmessage = Text(loadMessage, 400.0f, 340.0f, 24.0f, 0.0f);
    loadmessage.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    loadmessage.Render();

    Text percent = Text(std::to_string(loadPercent) + "%", 400.0f, 260.0f, 24.0f, 0.0f);
    percent.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    percent.Render();

    Rectangle loadBar = Rectangle(400.0f, 50.0f, (loadPercent/100.0f) * 700.0f, 30.0f);
    loadBar.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    loadBar.Render();

    glfwSwapBuffers(window);
}