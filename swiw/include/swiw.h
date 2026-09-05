#pragma once
#include "swiw_def.h"


#ifdef __cplusplus
extern "C"
{
#endif

	// ============================================================
	//  Function Pointer Typedefs
	// ============================================================

	void SWIW_Init();

	void SWIW_Shutdown();

	void SWIW_Create();

	ISwiwAPICallResult* SWIW_RegisterCallback(void* self, SwiwCallbackFn callback, int32_t eventId, void* userData);

	void SWIW_UnregisterCallback(void* self, int32_t eventId);

	void SWIW_GetVersion(wchar_t* outVersion);


	// ============================================================
	//  Function Pointer Typedefs
	// ============================================================

	typedef void(CXX_CDECL* SWIW_Init_t)();
	typedef void(CXX_CDECL* SWIW_Shutdown_t)();
	typedef void(CXX_CDECL* SWIW_Create_t)();
	typedef void(CXX_CDECL* SWIW_RegisterCallback_t)();
	typedef void(CXX_CDECL* SWIW_UnregisterCallback_t)();
	typedef void(CXX_CDECL* SWIW_GetVersion_t)(wchar_t*);

#ifdef __cplusplus
}
#endif
