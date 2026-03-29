#include <iostream>
#include "CVector.h"
#include <map>;
#include <CPed.h>;


class RealismPlayer {
private:
	struct PlayerBones {
		float head;
	};

	PlayerBones bones;

public:

	void HurtBone();
	PlayerBones& GetBones() { return bones; }
};