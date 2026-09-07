/*
 * file: swiw.h
 *
 */

#pragma once
#include "swiw_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================
//  Function Pointer Typedefs
// ============================================================

void SWIW_Init(const ISwiwInitConfig* config);

void SWIW_Shutdown();

ISwiwObject* SWIW_CreateObject(int32_t type_kind);

ISwiwAPICallResult* SWIW_RegisterCallback(void* self, SwiwCallbackFn callback,
                                          int32_t eventId, void* user_data);

void SWIW_UnregisterCallback(void* self, int32_t eventId);

void SWIW_CreateWebView(const ISwiwCreateWebViewConfig* config);

void SWIW_CreateWebUI(const ISwiwCreateWebUIConfig* config);

void SWIW_GetVersion(wchar_t* outVersion);

// ============================================================
//  Function Pointer Typedefs
// ============================================================

typedef void(CXX_CDECL* SWIW_Init_t)(const ISwiwInitConfig*);
typedef void(CXX_CDECL* SWIW_Shutdown_t)();
typedef ISwiwObject*(CXX_CDECL* SWIW_CreateConfig_t)(int32_t);
typedef ISwiwAPICallResult*(CXX_CDECL* SWIW_RegisterCallback_t)(void*,
                                                                SwiwCallbackFn,
                                                                int32_t, void*);
typedef void(CXX_CDECL* SWIW_UnregisterCallback_t)(void*, int32_t);
typedef void(CXX_CDECL* SWIW_CreateWebView_t)(const ISwiwCreateWebViewConfig*);
typedef void(CXX_CDECL* SWIW_CreateWebUI_t)(const ISwiwCreateWebUIConfig*);
typedef void(CXX_CDECL* SWIW_GetVersion_t)(wchar_t*);

#ifdef __cplusplus
}
#endif
