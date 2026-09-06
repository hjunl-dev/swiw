#pragma once
#include "swiw_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================
//  Function Pointer Typedefs
// ============================================================

void SWIW_Init(const ISwiwInitParam* param);

void SWIW_Shutdown();

ISwiwObject* SWIW_CreateParam(int32_t param_kind);

ISwiwAPICallResult* SWIW_RegisterCallback(void* self, SwiwCallbackFn callback,
                                          int32_t eventId, void* user_data);

void SWIW_UnregisterCallback(void* self, int32_t eventId);

void SWIW_CreateWebView(const ISwiwCreateWebViewParam* param);

void SWIW_CreatePopup(const ISwiwCreatePopupParam* param);

void SWIW_GetVersion(wchar_t* outVersion);

// ============================================================
//  Function Pointer Typedefs
// ============================================================

typedef void(CXX_CDECL* SWIW_Init_t)(const ISwiwInitParam* param);
typedef void(CXX_CDECL* SWIW_Shutdown_t)();
typedef ISwiwObject*(CXX_CDECL* SWIW_CreateParam_t)(int32_t param_kind);
typedef ISwiwAPICallResult*(CXX_CDECL* SWIW_RegisterCallback_t)(
    void* self, SwiwCallbackFn callback, int32_t eventId, void* user_data);
typedef void(CXX_CDECL* SWIW_UnregisterCallback_t)(void* self, int32_t eventId);
typedef void(CXX_CDECL* SWIW_CreateWebView_t)(
    const ISwiwCreateWebViewParam* param);
typedef void(CXX_CDECL* SWIW_CreatePopup_t)(const ISwiwCreatePopupParam* param);
typedef void(CXX_CDECL* SWIW_GetVersion_t)(wchar_t* outVersion);

#ifdef __cplusplus
}
#endif
