#include <plugin.h>
#include <CMessages.h>
#include <CMenuManager.h>
#include <Windows.h>
#include <string>
#include <CFont.h>
#include <CSprite2d.h>
#include <CTxdStore.h>
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
    bool bInited = false;

    // Achievements TXD
    
    static CSprite2d cursor;
    static CSprite2d achno; // Non-exist achievement
    static CSprite2d achcar; // Achievement car


    //

    AchievementOption()
    {
        Events::initRwEvent += [this](){
            if (!bInited) {
                bInited = true;
                SetupNewPage();
                InitPage();

                int txd = CTxdStore::AddTxdSlot("ach_txd");
                CTxdStore::LoadTxd(txd, "MODELS\\TXD\\ACHV.TXD");
                CTxdStore::AddRef(txd);
                CTxdStore::PushCurrentTxd();

                CTxdStore::SetCurrentTxd(txd);
                
                
                cursor.SetTexture(const_cast<char*>("mouse"));
                achno.SetTexture(const_cast<char*>("ach_no"));
                
                CTxdStore::PopCurrentTxd();


            }
        };
        Events::menuDrawingEvent += [this]() {
            RenderAchievements();
        };

        Events::shutdownRwEvent += [] {
            CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("ach_txd"));
        };

    }

    void RenderAchievements() { // 1024x768
        if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEFS) {
            achno.Draw(200.0, 220.0, 80.0, 80.0, CRGBA(255, 255, 255, 255));
            char buffer[50];
            sprintf_s(buffer, "%d %d", FrontEndMenuManager.m_nMousePosX, FrontEndMenuManager.m_nMousePosY);
            CFont::PrintString(300.0, 200.0, buffer);
            cursor.Draw(FrontEndMenuManager.m_nMousePosX, FrontEndMenuManager.m_nMousePosY, 29.0, 31.0, CRGBA(255,255,255,255));
        }
    }

    void SetupNewPage() {
        CMenuScreen* ac_page = &aScreens[MENUPAGE_BRIEFS];
        memset(ac_page, 0, sizeof(CMenuScreen));
        FrontEndMenuManager.m_nNumberOfMenuOptions = 2;
        FrontEndMenuManager.m_nCurrentMenuEntry = 0;
        strncpy(ac_page->m_ScreenName, "FEP_BRI", 8);
        ac_page->m_nPreviousPage = MENUPAGE_PAUSE_MENU;
        ac_page->m_nParentEntry = 0;
        ac_page->m_aEntries[0].m_nAction = MENUACTION_BACK;
        strncpy(ac_page->m_aEntries[0].m_EntryName, "FEDS_TB", 8);
        ac_page->m_aEntries[0].m_nX = 130;
        ac_page->m_aEntries[0].m_nY = 360;
        ac_page->m_aEntries[0].m_nAlign = 0;
    }

    void InitPage() {
        CMenuScreen* pausePage = &aScreens[MENUPAGE_PAUSE_MENU];
        int slotindex = 4; // 5
        pausePage->m_aEntries[slotindex].m_nAction = MENUACTION_CHANGEMENU;
        pausePage->m_aEntries[slotindex].m_nTargetMenu = MENUPAGE_BRIEFS;
        strncpy(pausePage->m_aEntries[slotindex].m_EntryName, "FEP_BRI", 8);
        pausePage->m_aEntries[slotindex + 1].m_nAction = MENUACTION_CHANGEMENU;
        pausePage->m_aEntries[slotindex + 1].m_nTargetMenu = MENUPAGE_EXIT;
        strncpy(pausePage->m_aEntries[slotindex + 1].m_EntryName, "FEP_QUI", 8);
    }

} mainInstance;

CSprite2d AchievementOption::achno;
CSprite2d AchievementOption::cursor;
CSprite2d AchievementOption::achcar;