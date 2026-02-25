#include <plugin.h> // Plugin-SDK version 1002 from 2025-12-09 23:18:09
#include <CMessages.h>
#include <CMenuManager.h>
#include <Windows.h>
#include <iostream>

using namespace plugin;

struct Main
{
    bool isDone;

    Main()
    {
        Events::menuDrawingEvent += [this]() { DrawMenu(); };
    }

    void DrawMenu() {
        CMenuManager* menu = &FrontEndMenuManager;
        if ((menu->m_bMenuActive && menu->m_nCurrentMenuPage == MENUPAGE_OPTIONS) && isDone == false) {
            menu-> // update soon =)
        }
    }

};

Main mainInstance;