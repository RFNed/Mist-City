#include <plugin.h>
#include <CMessages.h>
#include <CMenuManager.h>
#include <Windows.h>
#include <string>
#include <CFont.h>
#include <CSprite2d.h>
#include <CTxdStore.h>
#include <iostream>
#include "Functions.h"

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

enum cursors
{
    CursorPoint = 4,
    CursorHand = 5
};

struct AchievementOption
{
    bool bInited = false;
    bool fInited = false;

    int currentCursor;
    
    static CSprite2d cursor_point;
	static CSprite2d cursor_hand;
    static CSprite2d achno; // Non-exist achievement
    static CSprite2d achcar; // Achievement car
    
    AchievementOption()
    {
        Events::initGameEvent += [this]() {

            };
        Events::gameProcessEvent += [this]() {
        };
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
                
                
                cursor_point.SetTexture(const_cast<char*>("mouse"));
				cursor_hand.SetTexture(const_cast<char*>("hand"));
                achno.SetTexture(const_cast<char*>("ach_no"));
                achcar.SetTexture(const_cast<char*>("ach_car"));
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

    void RenderAchievements() {
        ShowCursor(TRUE);
        constexpr float baseW = 1024.0f;
        constexpr float baseH = 768.0f;
        
        float screenW = (float)RsGlobal.maximumWidth;
        float screenH = (float)RsGlobal.maximumHeight;

        float scaleX = screenW / baseW;
        float scaleY = screenH / baseH;
        float scale = (scaleX + scaleY) / 2.0f;
        float fontScale = std::min(scaleX, scaleY);
        currentCursor = CursorPoint;
        if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEFS) {

            


            struct SpritePos {
                int scmIndex;
                float xRel, yRel;
                CSprite2d& spriteYes;
                CSprite2d& spriteNo;
                char desc[50];
            };

            SpritePos sprites[] = {
                {2, 0.195f, 0.2864f, achcar, achno, "Y™o®œ ¯a¥œ®y!~n~“¦o ¢ecežo!"},
                {3, 0.305f, 0.2864f, achcar, achno, "Achievement 2"}
            };

            for (auto& sp : sprites) {
                
                int value = GetSCMGlobal(sp.scmIndex);

                CSprite2d& spriteToDraw = (value == 1) ? sp.spriteYes : sp.spriteNo;

                float posX = screenW * sp.xRel;
                float posY = screenH * sp.yRel;
                spriteToDraw.Draw(posX, posY, 87.0f * scale, 87.0f * scale, CRGBA(255, 255, 255, 255));
                float hoverX = screenW * sp.xRel;
                float hoverY = screenH * sp.yRel;
                float spriteSize = 87.0f * scale;
                if (
                    (FrontEndMenuManager.m_nMousePosX > hoverX &&
                    FrontEndMenuManager.m_nMousePosX < hoverX + spriteSize &&
                    FrontEndMenuManager.m_nMousePosY > hoverY &&
                    FrontEndMenuManager.m_nMousePosY < hoverY + spriteSize)
                    
                    )
                {
                    currentCursor = CursorHand;
                    if (value == 0) {
                        CFont::SetFontStyle(FONT_SUBTITLES);
                        CFont::SetScale(0.8f * scaleX, 1.3f * scaleY);
                        CFont::PrintString(screenW * 0.58f, screenH * 0.75f, sp.desc);
                    }
                }
            }





            char buffer[50];
            sprintf_s(buffer, "%d %d", FrontEndMenuManager.m_nMousePosX, FrontEndMenuManager.m_nMousePosY);
            CFont::SetScale(0.9f * fontScale, 0.9f * fontScale);
            CFont::PrintString(screenW * 0.5f, screenH * 0.15f, buffer);

            if (currentCursor == CursorPoint) {
                cursor_point.Draw((float)FrontEndMenuManager.m_nMousePosX,
                    (float)FrontEndMenuManager.m_nMousePosY,
                    29.0f * scaleX, 31.0f * scaleY,
                    CRGBA(255, 255, 255, 255));
            }
            else if (currentCursor == CursorHand) {
                ShowCursor(FALSE);
                cursor_hand.Draw((float)FrontEndMenuManager.m_nMousePosX,
                    (float)FrontEndMenuManager.m_nMousePosY,
                    29.0f * scaleX, 31.0f * scaleY,
                    CRGBA(255, 255, 255, 255));
            }

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
CSprite2d AchievementOption::cursor_point;
CSprite2d AchievementOption::cursor_hand;
CSprite2d AchievementOption::achcar;