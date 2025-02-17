#include <Windows.h>

#include "render/imgui.h"
#include "hooks/hooks.h"

//
//		THIS WAS MADE BY @THEREALJOELMATIC
//

void EntryPoint() {
	dx11Hook::init();

	if (!hooks::init()) {
		MessageBoxA(nullptr, "Failed to initialize hooks", "Error", MB_OK);
	}
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)EntryPoint, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}