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
    static CSprite2d ach_car;
    AchievementOption()
    {
        Events::initRwEvent += [this](){
            if (!bInited) {
                SetupNewPage();
                InitPage();

                int ach_txd = CTxdStore::AddTxdSlot("ach_txd");

                CTxdStore::LoadTxd(ach_txd, "MODELS\\ACHV.TXD");
                CTxdStore::AddRef(ach_txd);
                CTxdStore::PushCurrentTxd();
                CTxdStore::SetCurrentTxd(ach_txd);
                
                ach_car.SetTexture("ach1", NULL);
                CTxdStore::PopCurrentTxd();

                bInited = true;
            }
        };
        Events::menuDrawingEvent += [this]() {
            RenderAchievements();
        };

        Events::shutdownRwEvent += [] {
            ach_car.Delete();
            CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("ach_txd"));
        }

    }

    void RenderAchievements() {
        if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEFS) {
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