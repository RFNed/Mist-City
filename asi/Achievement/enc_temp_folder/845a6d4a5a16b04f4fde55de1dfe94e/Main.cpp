#include <plugin.h> // Plugin-SDK version 1002 from 2025-12-09 23:18:09
#include <CMessages.h>
#include <CMenuManager.h>
#include <Windows.h>
#include <string>
#include <CFont.h>
#define SCM_GLOBALS_BASE 0xA49960

using namespace plugin;

int GetSCMGlobal(int index) {
    int val = 0;
    int* ptr = (int*)(SCM_GLOBALS_BASE + index * 4);
    __try {
        memcpy(&val, ptr, sizeof(int));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        val = 0;
    }
    return val;
}

struct AchievementOption
{
    bool isDone = false;
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
        Events::gameProcessEvent += [this]() {
            Test();
        };
    }

    void Test() {
        if (isDone == false) {
            int var = GetSCMGlobal(6);
            __try {
                int value = var;
                char buffer[64];
                sprintf_s(buffer, "is %d", value);
                if (value != 17) {
                    CMessages::AddMessageJumpQ(buffer, 100, 1);
                } else {
                    MessageBox(
                        NULL,
                        "OK",
                        "OK",
                        MB_CANCELTRYCONTINUE | MB_ICONQUESTION
                    );
                    isDone = true;
                    CMessages::AddBigMessage("yoyoyo", 5000, 1);
                    CMessages::AddMessageJumpQ("its Done! Thank you!!!", 5000, 1);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                CMessages::AddMessageJumpQ("SCMGlobal access violation", 100, 1);
            }
        }
    }

    void SetupNewPage() {

        CMenuScreen* ac_page = &aScreens[MENUPAGE_BRIEFS];

        memset(ac_page, 0, sizeof(CMenuScreen));

        FrontEndMenuManager.m_nNumberOfMenuOptions = 2;
        FrontEndMenuManager.m_nCurrentMenuEntry = 0;

        strncpy(ac_page->m_ScreenName, "FEP_BRI", 8);

        ac_page->m_nPreviousPage = MENUPAGE_MAIN_MENU;
        ac_page->m_nParentEntry = 0;


        ac_page->m_aEntries[0].m_nAction = MENUACTION_BACK_PC;
        strncpy(ac_page->m_aEntries[0].m_EntryName, "FEDS_TB", 8);

        ac_page->m_aEntries[0].m_nX = 150;
        ac_page->m_aEntries[0].m_nY = 190;

        ac_page->m_aEntries[0].m_nAlign = 0;

        ac_page->m_aEntries[1].m_nAction = MENUACTION_BACK_PC;
        strncpy(ac_page->m_aEntries[1].m_EntryName, "FED_DBG", 8); 
        ac_page->m_aEntries[1].m_nAlign = 0;
        
        
    }

    void InitPage() {
        CMenuScreen* pausePage = &aScreens[MENUPAGE_MAIN_MENU];

        int slotindex = 4; // 5
        pausePage->m_aEntries[slotindex].m_nAction = MENUACTION_CHANGEMENU;
        pausePage->m_aEntries[slotindex].m_nTargetMenu = MENUPAGE_BRIEFS;
        strncpy(pausePage->m_aEntries[slotindex].m_EntryName, "FEP_BRI", 8);
    }

} mainInstance;