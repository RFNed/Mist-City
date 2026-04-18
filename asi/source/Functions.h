#include <iostream>
#include "CVector.h"
#include <map>
#include <CPed.h>
#include <string>



class RlPlayer {

private:
	float health;
	float armour;
	CPed* ped;
public:
	RlPlayer(float Health = 100.0f, CPed* ped = nullptr) : health(Health), ped(ped) {}
	float GetHealth();
	void takePlayerData();
	void ProcessHealthAffect();
};