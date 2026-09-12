/*
 * file: swiw_flat.h
 *
 *   C flat API for SWIW interfaces.
 *   Pure C consumers include this header only (it pulls in swiw_def.h).
 *
 *   Naming rule : SWIW_<Interface>_<Method>
 *   Self param  : const T* for observers, T* for mutators / Release
 *   Null-safe   : every function tolerates a NULL self (returns a default)
 */

#pragma once

#include "swiw_def.h"

/* ------------------------------------------------------------
 *  Linkage / calling convention
 * ------------------------------------------------------------ */

#if defined(_WIN32)
#if defined(SWIW_BUILD_DLL)
#define SWIW_API __declspec(dllexport)
#elif defined(SWIW_USE_DLL)
#define SWIW_API __declspec(dllimport)
#else
#define SWIW_API
#endif
#else
#if defined(SWIW_BUILD_DLL)
#define SWIW_API __attribute__((visibility("default")))
#else
#define SWIW_API
#endif
#endif

#define SWIW_CALL CXX_CDECL

#ifndef __cplusplus
/*
 * swiw_def.h's pure-C branch declares `ISwiwInitParam`, but the C++ branch
 * declares `ISwiwInitConfig`. Forward-declare the config name here so the C
 * side matches the C++ ABI. (Fixing swiw_def.h itself is preferable.)
 */
typedef struct ISwiwInitConfig ISwiwInitConfig;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------
 *  Static type kinds (C++ side: k_eStaticTypeKind)
 * ------------------------------------------------------------ */

#define SWIW_ISwiwObject_kStaticTypeKind k_ESwiwTypeKind_Object
#define SWIW_ISwiwAPICallResult_kStaticTypeKind k_ESwiwTypeKind_ApiCallResult
#define SWIW_ISwiwRect_kStaticTypeKind k_ESwiwTypeKind_Rect
#define SWIW_ISwiwInitConfig_kStaticTypeKind k_ESwiwTypeKind_InitConfig
#define SWIW_ISwiwCreateWebViewConfig_kStaticTypeKind \
  k_ESwiwTypeKind_CreateWebViewConfig
#define SWIW_ISwiwCreateWebUIConfig_kStaticTypeKind \
  k_ESwiwTypeKind_CreateWebUIConfig

/* ============================================================
 *  ISwiwObject
 * ============================================================ */

SWIW_API int32_t SWIW_CALL SWIW_ISwiwObject_GetType(const ISwiwObject* self);
SWIW_API bool SWIW_CALL SWIW_ISwiwObject_GetOwnership(const ISwiwObject* self);
SWIW_API void SWIW_CALL SWIW_ISwiwObject_Release(ISwiwObject* self);
SWIW_API void* SWIW_CALL SWIW_ISwiwObject_Query(const ISwiwObject* self,
                                                int32_t id);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwObject_ToString(const ISwiwObject* self);

/* ============================================================
 *  ISwiwAPICallResult
 * ============================================================ */

/* -- ISwiwObject part -- */
SWIW_API int32_t SWIW_CALL
SWIW_ISwiwAPICallResult_GetType(const ISwiwAPICallResult* self);
SWIW_API bool SWIW_CALL
SWIW_ISwiwAPICallResult_GetOwnership(const ISwiwAPICallResult* self);
SWIW_API void SWIW_CALL
SWIW_ISwiwAPICallResult_Release(ISwiwAPICallResult* self);
SWIW_API void* SWIW_CALL
SWIW_ISwiwAPICallResult_Query(const ISwiwAPICallResult* self, int32_t id);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwAPICallResult_ToString(const ISwiwAPICallResult* self);

/* -- casts -- */
SWIW_API ISwiwObject* SWIW_CALL
SWIW_ISwiwAPICallResult_AsObject(ISwiwAPICallResult* self);
SWIW_API const ISwiwObject* SWIW_CALL
SWIW_ISwiwAPICallResult_AsObjectConst(const ISwiwAPICallResult* self);
SWIW_API ISwiwAPICallResult* SWIW_CALL
SWIW_ISwiwAPICallResult_CastFromObject(ISwiwObject* obj);
SWIW_API const ISwiwAPICallResult* SWIW_CALL
SWIW_ISwiwAPICallResult_CastFromObjectConst(const ISwiwObject* obj);

/* -- own methods -- */
SWIW_API bool SWIW_CALL
SWIW_ISwiwAPICallResult_IsOk(const ISwiwAPICallResult* self);
SWIW_API int32_t SWIW_CALL
SWIW_ISwiwAPICallResult_GetErrorCode(const ISwiwAPICallResult* self);
SWIW_API int32_t SWIW_CALL
SWIW_ISwiwAPICallResult_GetApiCode(const ISwiwAPICallResult* self);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwAPICallResult_GetErrorMsg(const ISwiwAPICallResult* self);

/* ============================================================
 *  ISwiwRect
 * ============================================================ */

/* -- ISwiwObject part -- */
SWIW_API int32_t SWIW_CALL SWIW_ISwiwRect_GetType(const ISwiwRect* self);
SWIW_API bool SWIW_CALL SWIW_ISwiwRect_GetOwnership(const ISwiwRect* self);
SWIW_API void SWIW_CALL SWIW_ISwiwRect_Release(ISwiwRect* self);
SWIW_API void* SWIW_CALL SWIW_ISwiwRect_Query(const ISwiwRect* self,
                                              int32_t id);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwRect_ToString(const ISwiwRect* self);

/* -- casts -- */
SWIW_API ISwiwObject* SWIW_CALL SWIW_ISwiwRect_AsObject(ISwiwRect* self);
SWIW_API const ISwiwObject* SWIW_CALL
SWIW_ISwiwRect_AsObjectConst(const ISwiwRect* self);
SWIW_API ISwiwRect* SWIW_CALL SWIW_ISwiwRect_CastFromObject(ISwiwObject* obj);
SWIW_API const ISwiwRect* SWIW_CALL
SWIW_ISwiwRect_CastFromObjectConst(const ISwiwObject* obj);

/* -- own methods -- */
SWIW_API int32_t SWIW_CALL SWIW_ISwiwRect_GetX(const ISwiwRect* self);
SWIW_API void SWIW_CALL SWIW_ISwiwRect_SetX(ISwiwRect* self, int32_t x);
SWIW_API int32_t SWIW_CALL SWIW_ISwiwRect_GetY(const ISwiwRect* self);
SWIW_API void SWIW_CALL SWIW_ISwiwRect_SetY(ISwiwRect* self, int32_t y);
SWIW_API int32_t SWIW_CALL SWIW_ISwiwRect_GetWidth(const ISwiwRect* self);
SWIW_API void SWIW_CALL SWIW_ISwiwRect_SetWidth(ISwiwRect* self, int32_t width);
SWIW_API int32_t SWIW_CALL SWIW_ISwiwRect_GetHeight(const ISwiwRect* self);
SWIW_API void SWIW_CALL SWIW_ISwiwRect_SetHeight(ISwiwRect* self,
                                                 int32_t height);

/* ============================================================
 *  ISwiwInitConfig
 * ============================================================ */

/* -- ISwiwObject part -- */
SWIW_API int32_t SWIW_CALL
SWIW_ISwiwInitConfig_GetType(const ISwiwInitConfig* self);
SWIW_API bool SWIW_CALL
SWIW_ISwiwInitConfig_GetOwnership(const ISwiwInitConfig* self);
SWIW_API void SWIW_CALL SWIW_ISwiwInitConfig_Release(ISwiwInitConfig* self);
SWIW_API void* SWIW_CALL SWIW_ISwiwInitConfig_Query(const ISwiwInitConfig* self,
                                                    int32_t id);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwInitConfig_ToString(const ISwiwInitConfig* self);

/* -- casts -- */
SWIW_API ISwiwObject* SWIW_CALL
SWIW_ISwiwInitConfig_AsObject(ISwiwInitConfig* self);
SWIW_API const ISwiwObject* SWIW_CALL
SWIW_ISwiwInitConfig_AsObjectConst(const ISwiwInitConfig* self);
SWIW_API ISwiwInitConfig* SWIW_CALL
SWIW_ISwiwInitConfig_CastFromObject(ISwiwObject* obj);
SWIW_API const ISwiwInitConfig* SWIW_CALL
SWIW_ISwiwInitConfig_CastFromObjectConst(const ISwiwObject* obj);

/* -- own methods -- */
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwInitConfig_GetUdfPath(const ISwiwInitConfig* self);
SWIW_API void SWIW_CALL
SWIW_ISwiwInitConfig_SetUdfPath(ISwiwInitConfig* self, const wchar_t* udf_path);

/* ============================================================
 *  ISwiwCreateWebViewConfig
 * ============================================================ */

/* -- ISwiwObject part -- */
SWIW_API int32_t SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_GetType(const ISwiwCreateWebViewConfig* self);
SWIW_API bool SWIW_CALL SWIW_ISwiwCreateWebViewConfig_GetOwnership(
    const ISwiwCreateWebViewConfig* self);
SWIW_API void SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_Release(ISwiwCreateWebViewConfig* self);
SWIW_API void* SWIW_CALL SWIW_ISwiwCreateWebViewConfig_Query(
    const ISwiwCreateWebViewConfig* self, int32_t id);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_ToString(const ISwiwCreateWebViewConfig* self);

/* -- casts -- */
SWIW_API ISwiwObject* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_AsObject(ISwiwCreateWebViewConfig* self);
SWIW_API const ISwiwObject* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_AsObjectConst(
    const ISwiwCreateWebViewConfig* self);
SWIW_API ISwiwCreateWebViewConfig* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_CastFromObject(ISwiwObject* obj);
SWIW_API const ISwiwCreateWebViewConfig* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_CastFromObjectConst(const ISwiwObject* obj);

/* -- own methods -- */
SWIW_API const ISwiwRect* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_GetRect(const ISwiwCreateWebViewConfig* self);
SWIW_API void SWIW_CALL SWIW_ISwiwCreateWebViewConfig_SetRect(
    ISwiwCreateWebViewConfig* self, const ISwiwRect* rect);
SWIW_API void SWIW_CALL SWIW_ISwiwCreateWebViewConfig_SetRectValues(
    ISwiwCreateWebViewConfig* self, int32_t x, int32_t y, int32_t w, int32_t h);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwCreateWebViewConfig_GetUri(const ISwiwCreateWebViewConfig* self);
SWIW_API void SWIW_CALL SWIW_ISwiwCreateWebViewConfig_SetUri(
    ISwiwCreateWebViewConfig* self, const wchar_t* uri);

/* ============================================================
 *  ISwiwCreateWebUIConfig
 * ============================================================ */

/* -- ISwiwObject part -- */
SWIW_API int32_t SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_GetType(const ISwiwCreateWebUIConfig* self);
SWIW_API bool SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_GetOwnership(const ISwiwCreateWebUIConfig* self);
SWIW_API void SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_Release(ISwiwCreateWebUIConfig* self);
SWIW_API void* SWIW_CALL SWIW_ISwiwCreateWebUIConfig_Query(
    const ISwiwCreateWebUIConfig* self, int32_t id);
SWIW_API const wchar_t* SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_ToString(const ISwiwCreateWebUIConfig* self);

/* -- casts -- */
SWIW_API ISwiwObject* SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_AsObject(ISwiwCreateWebUIConfig* self);
SWIW_API const ISwiwObject* SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_AsObjectConst(const ISwiwCreateWebUIConfig* self);
SWIW_API ISwiwCreateWebUIConfig* SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_CastFromObject(ISwiwObject* obj);
SWIW_API const ISwiwCreateWebUIConfig* SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_CastFromObjectConst(const ISwiwObject* obj);

/* -- own methods -- */
SWIW_API const ISwiwRect* SWIW_CALL
SWIW_ISwiwCreateWebUIConfig_GetRect(const ISwiwCreateWebUIConfig* self);
SWIW_API void SWIW_CALL SWIW_ISwiwCreateWebUIConfig_SetRect(
    ISwiwCreateWebUIConfig* self, const ISwiwRect* rect);
SWIW_API void SWIW_CALL SWIW_ISwiwCreateWebUIConfig_SetRectValues(
    ISwiwCreateWebUIConfig* self, int32_t x, int32_t y, int32_t w, int32_t h);

#ifdef __cplusplus
}  // extern "C"
#endif
