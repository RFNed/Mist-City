#include <plugin.h> // Plugin-SDK version 1002 from 2025-12-09 23:18:09
#include <CMessages.h>

using namespace plugin;

struct Main
{
    size_t m_frame = 0; // render frame counter

    Main()
    {
        // register event callbacks
        Events::gameProcessEvent += []{ gInstance.OnGameProcess(); };
    }

    void OnGameProcess()
    {
        m_frame++;
        
        static char msg[255];
        sprintf_s(msg, "Hello from '%s' plugin! Frame %d", TARGET_NAME, m_frame);
        
        CMessages::AddMessageJumpQ(msg, 500, 0);
    }
} gInstance;
