/** @file Main.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "Mod\Mod.hpp"

#include <Windows.h>
#include <memory>

#include <scssdk_telemetry.h>

static std::unique_ptr<Mod> g_pMod;

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t *const params)
{
	if (version != SCS_TELEMETRY_VERSION_1_00)
		return SCS_RESULT_unsupported;

	g_pMod = std::make_unique<Mod>();
	return g_pMod->Init((scs_telemetry_init_params_v100_t*)params);
}

SCSAPI_VOID scs_telemetry_shutdown(void)
{
	g_pMod.reset();
}

int WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_DETACH:
		{
			g_pMod.reset();
		} break;
	}

	return TRUE;
}
