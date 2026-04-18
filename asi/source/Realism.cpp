#include "Functions.h"
#include <CPlayerPed.h>
#include <CPed.h>
#include <Windows.h>
#include <string>
#include <plugin.h>
using namespace std;


string RlPlayer::GetName() {
	return name;
}

float RlPlayer::GetHealth() {
	return RlPlayer::health;
}

void RlPlayer::takePlayerData() {
	RlPlayer::ped = FindPlayerPed();
	RlPlayer::health = ped->m_fHealth;
}