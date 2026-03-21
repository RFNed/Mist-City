#include "Functions.h"
#include <Windows.h>

CVector Player::GetPosition() {
    DWORD ped = 0xB6F5F0;

    // Координаты игрока лежат по оффсету 0x56C в CPed
    CVector* pos = (CVector*)((ped + 0x14C));
    return *pos;
}

