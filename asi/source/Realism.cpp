#include "Functions.h"
#include <CPlayerPed.h>
#include <CPed.h>
#include <Windows.h>
#include <string>
#include <CCamera.h>
#include <plugin.h>
#include <effects.h>
#include <CStats.h>
using namespace std;

float RlPlayer::GetHealth() {
	return RlPlayer::health;
}

void RlPlayer::takePlayerData() {
	RlPlayer::ped = FindPlayerPed();
	RlPlayer::health = ped->m_fHealth;
	RlPlayer::armour = ped->m_fArmour;
}

void RlPlayer::ProcessHealthAffect() {
	if (this->ped->IsAlive()) {
		float currentHealth = this->ped->m_fHealth;
		if (currentHealth < this->health) {
			float damage = this->health - currentHealth;
			int ReasonDamage = (ped->m_nLastWeaponDamage);

			switch (ReasonDamage)
			{
			case 0:
				if (damage < 3.0f) {
					TheCamera.LerpFOV(90.0f, 130.0f, 10.0f, true);
					
				}
				break;
			}

			OutputDebugStringA(("Player took damage: " + to_string(damage) + + " -> WeaponID: " + to_string(ReasonDamage) + "\n").c_str());
		}
		RlPlayer::health = currentHealth;
	}
}