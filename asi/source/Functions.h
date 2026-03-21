#include <iostream>
#include "CVector.h"
struct CPed;

class Player {
private:
	DWORD playerDataAddr = 0xB7CD98;
public:
	CVector GetPosition();
};