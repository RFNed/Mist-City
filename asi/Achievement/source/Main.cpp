#include <plugin.h> // Plugin-SDK version 1002 from 2025-12-09 23:18:09
#include <CMessages.h>
#include <CMenuManager.h>
#include <Windows.h>
#include <iostream>
#include <CFont.h>

using namespace plugin;

struct AchievementOption
{

    bool bInited = false;

    AchievementOption()
    {
        Events::initRwEvent += [this](){
            if (!bInited) {
                SetupNewPage();
                InitPage();
                bInited = true;
            }
        };
        Events::drawMenuBackgroundEvent += [this]() {DebugText();};
    }
    // debug
    void DebugText() {
        CMenuManager* screen = &FrontEndMenuManager;
        if (screen->m_nCurrentMenuPage == MENUPAGE_BRIEFS) {
            char buffer[128];
            sprintf_s(buffer, "%d %d %d %d", screen->m_nMousePosX, screen->m_nMousePosY, screen->m_nMouseOldPosX, screen->m_nMouseOldPosY);
            CFont::PrintString(400.0f, 150.0f, buffer);
        }
    }

    void SetupNewPage() {
        CMenuScreen* ac_page = &aScreens[MENUPAGE_BRIEFS];
        strncpy(ac_page->m_ScreenName, "FEP_BRI", 8);
        ac_page->m_nPreviousPage = MENUPAGE_PAUSE_MENU;
        ac_page->m_nParentEntry = 0;

        for (int i = 0; i < NUM_ENTRIES; i++) {
            ac_page->m_aEntries[i].m_nAction = MENUACTION_NOTHING;
        }

        ac_page->m_aEntries[0].m_nAction = MENUACTION_BACK_PC;
        strncpy(ac_page->m_aEntries[0].m_EntryName, "FEP_BRI", 8);

        ac_page->m_aEntries[0].m_nAlign = 1;
        ac_page->m_aEntries[0].m_nX = 320;
        ac_page->m_aEntries[0].m_nY = 200;
        
        
    }

    void InitPage() {
        CMenuScreen* pausePage = &aScreens[MENUPAGE_PAUSE_MENU];

        int slotindex = 5;
        pausePage->m_aEntries[slotindex].m_nAction = MENUACTION_CHANGEMENU;
        pausePage->m_aEntries[slotindex].m_nTargetMenu = MENUPAGE_BRIEFS;
        strncpy(pausePage->m_aEntries[slotindex].m_EntryName, "FEP_BRI", 8);
    }

} mainInstance;