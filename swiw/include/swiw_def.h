/*
 * file: swiw_def.h
 *
 */

#pragma once
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

// ============================================================
//  Common defines
// ============================================================

#if defined(_MSC_VER) && _MSC_VER < 1900
#define CXX_CONSTEXPR const
#else
#define CXX_CONSTEXPR constexpr
#endif

#if defined(_MSC_VER)
#define CXX_CDECL __cdecl
#else
#define CXX_CDECL
#endif

// ============================================================
//  Enum
// ============================================================

//
// TypeKind
//
typedef enum ESwiwTypeKind {
  k_ESwiwTypeKind_Invalid = -1,

  // 0~499: common objects
  k_ESwiwTypeKind_Object = 0,
  k_ESwiwTypeKind_ApiCallResult = 1,

  // 500~999: util objects
  k_ESwiwTypeKind_Rect = 500,

  // 1000~1999: params
  k_ESwiwTypeKind_InitConfig = 1000,
  k_ESwiwTypeKind_CreateWebViewConfig = 1002,
  k_ESwiwTypeKind_CreateWebUIConfig = 1003,

  k_ESwiwTypeKind_Max = 0x7fffffff,
} ESwiwTypeKind;

//
// ErrorKind
//
typedef enum ESwiwErrorKind {
  k_ESwiwErrorCode_Invalid = -1,

  k_ESwiwErrorCode_Ok = 0,
  k_ESwiwErrorCode_Fail = 1,

  k_ESwiwErrorCode_Max = 0x7fffffff,
} ESwiwErrorCode;

// ============================================================
//  Interface
// ============================================================

#ifdef __cplusplus

#define SWIW_TYPE_KIND_DEF_STATIC(TypeKind) \
  static CXX_CONSTEXPR ESwiwTypeKind k_eStaticTypeKind = TypeKind

//
// ISwiwObject
//
struct ISwiwObject {
  SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_Object);

  virtual int32_t GetType() const = 0;
  virtual bool GetOwnership() const = 0;
  virtual void Release() = 0;
  virtual void* Query(int32_t id) const = 0;
  virtual const wchar_t* ToString() const = 0;
};

//
// ISwiwAPICallResult
//
struct ISwiwAPICallResult : ISwiwObject {
  SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_ApiCallResult);

  virtual bool IsOk() const = 0;
  virtual int32_t GetErrorCode() const = 0;
  virtual int32_t GetApiCode() const = 0;
  virtual const wchar_t* GetErrorMsg() const = 0;
};

//
// ISwiwRect
//
struct ISwiwRect : ISwiwObject {
  SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_Rect);

  virtual int32_t GetX() const = 0;
  virtual void SetX(int32_t x) = 0;
  virtual int32_t GetY() const = 0;
  virtual void SetY(int32_t y) = 0;
  virtual int32_t GetWidth() const = 0;
  virtual void SetWidth(int32_t width) = 0;
  virtual int32_t GetHeight() const = 0;
  virtual void SetHeight(int32_t height) = 0;
};

//
// ISwiwInitConfig
//
struct ISwiwInitConfig : ISwiwObject {
  SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_InitConfig);

  // user data folder path
  virtual const wchar_t* GetUdfPath() const = 0;
  virtual void SetUdfPath(const wchar_t* udf_path) = 0;
};

//
// ISwiwCreateViewParam
//
struct ISwiwCreateWebViewConfig : ISwiwObject {
  SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_CreateWebViewConfig);

  virtual const ISwiwRect* GetRect() const = 0;
  virtual void SetRect(const ISwiwRect* rect) = 0;
  virtual void SetRectValues(int32_t x, int32_t y, int32_t w, int32_t h) = 0;

  virtual const wchar_t* GetUri() const = 0;
  virtual void SetUri(const wchar_t* uri) = 0;
};
//
// ISwiwCreateWebUIParam
//
struct ISwiwCreateWebUIConfig : ISwiwObject {
  SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_CreateWebUIConfig);

  virtual const ISwiwRect* GetRect() const = 0;
  virtual void SetRect(const ISwiwRect* rect) = 0;
  virtual void SetRectValues(int32_t x, int32_t y, int32_t w, int32_t h) = 0;
};
#else
// pure c (opaque handle)
typedef struct ISwiwObject ISwiwObject;
typedef struct ISwiwAPICallResult ISwiwAPICallResult;
typedef struct ISwiwRect ISwiwRect;
typedef struct ISwiwInitParam ISwiwInitParam;
typedef struct ISwiwCreateWebViewConfig ISwiwCreateWebViewConfig;
typedef struct ISwiwCreateWebUIConfig ISwiwCreateWebUIConfig;
#endif  // __cplusplus

// ============================================================
//  Callback
// ============================================================

typedef void(CXX_CDECL* SwiwCallbackFn)(void* self,
                                        const ISwiwAPICallResult* res,
                                        const ISwiwObject* payload);
