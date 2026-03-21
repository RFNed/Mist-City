#include <plugin.h>
#include <CMessages.h>
#include <CMenuManager.h>
#include <Windows.h>
#include <string>
#include <CFont.h>
#include <CSprite2d.h>
#include <CTxdStore.h>

using namespace plugin;

struct Realism {
	
	bool isPrinted;
	
	Realism() {


		Events::gameProcessEvent += [this]() {
			Test();
		};
		


	}
	void Test() {
		if (!isPrinted) {
			CMessages::AddBigMessage("hello world", 3000, 1);
			isPrinted = true;
		}
	}
} RealismInstance;