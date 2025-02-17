#include "hooks.h"

#include "../../ext/maticHook/maticHook.hpp"

#include <Windows.h>
#include <iostream>

uintptr_t module_base;

namespace offsets {
    uintptr_t addloot = 0x3c6e3f0;
    uintptr_t battlePass = 0x3c717e0;
}

typedef int32_t(WINAPI* set_BuyBattlePass)(void* a1, void* a2, bool isPremium);
set_BuyBattlePass original_BuyBattlePass;

typedef int32_t(WINAPI* set_AddLoot)(void* a1, void* a2, void* lootID);
set_AddLoot original_AddLoot;

int32_t __fastcall hk_AddLoot(void* a1, void* a2, void* lootID) {
    std::cout << "Loot: " << std::hex << lootID << std::endl;

    uintptr_t lpTarget = module_base + offsets::battlePass;
    original_BuyBattlePass = (set_BuyBattlePass)lpTarget;

    original_BuyBattlePass(a1, a2, true); //unlock the battlepass

    return original_AddLoot(a1, a2, lootID);
}

bool hooks::init() {
    if (!maticHook::init())
		return false;

    module_base = (uintptr_t)GetModuleHandleA("Project.dll");
    if (!module_base) 
        return false;


    /*
    this is add loot
    Found Adress: 3c6e3f0
    Hooks Initialized
    Loot: 0000000002000005
    This is battlePass
    Found Adress: 3c717e0
    */

    //make hook
    uintptr_t lpTarget = module_base + offsets::addloot;
    maticHook::create((void*)lpTarget, hk_AddLoot, reinterpret_cast<void*&>(original_AddLoot));

    Beep(500, 500);

    return true;
}