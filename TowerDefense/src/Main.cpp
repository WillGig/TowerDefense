#include "pch.h"
#include "TowerDefense.h"

int main(void)
{
    if (!TowerDefense::Init())
        return -1;

    TowerDefense::Run();

    TowerDefense::CleanUp();

    return 0;
}