#include <iostream>
#include "CVector.h"
#include <map>
#include <CPed.h>
#include <string>



class RlPlayer {

private:
	std::string name;
	float health;
	CPed* ped;
public:
	RlPlayer(std::string TypeName = "Default", float Health = 100.0f, CPed* ped = nullptr) : name(TypeName), health(Health), ped(ped) {}
	float GetHealth();
	void takePlayerData();
	std::string GetName();
};