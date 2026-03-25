#include "Functions.h"
#include <Windows.h>

CVector Player::GetPosition() {
    DWORD ped = 0xB6F5F0;
    CVector* pos = (CVector*)((ped + 0x14C));
    return *pos;
}

