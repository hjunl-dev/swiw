/*
 * file: swiw_type.h
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
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
//  Type kinds
// ============================================================

typedef enum ESwiwTypeKind
{
	k_ESwiwTypeKind_Invalid = -1,

	// 0~999: common objects
	k_ESwiwTypeKind_Object = 0,
	k_ESwiwTypeKind_ApiCallResult = 1,

	// 1000~1999: params
	k_ESwiwTypeKind_InitParam = 1000,
	k_ESwiwTypeKind_CreateViewParam = 1001,

	k_ESwiwTypeKind_Max = 0x7fffffff,
} ESwiwTypeKind;



// ============================================================
//  Types
// ============================================================

#ifdef __cplusplus

#define SWIW_TYPE_KIND_DEF_STATIC(TypeKind) \
	static CXX_CONSTEXPR ESwiwTypeKind k_eStaticTypeKind = TypeKind

//
// ISwiwObject
//

struct ISwiwObject
{
	SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_Object);

	virtual int GetType() const = 0;
	virtual bool GetOwnership() const = 0;
	virtual void Release() const = 0;
	virtual void* Query() const = 0;
	virtual const wchar_t* ToString() const = 0;
};

//
// ISwiwAPICallResult
//

struct ISwiwAPICallResult : ISwiwObject
{
	SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_ApiCallResult);

	virtual bool IsOk() const = 0;
	virtual int32_t GetErrorCode() const = 0;
	virtual int32_t GetApiCode() const = 0;
	virtual const wchar_t* GetErrorMsg() = 0;
};

//
// ISwiwInitParam
//

struct ISwiwInitParam : ISwiwObject
{
	SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_InitParam);

	// user data folder path
	virtual const wchar_t* GetUdfPath() const = 0;
	virtual const void SetUdfPath(const wchar_t* udfPath) = 0;
};

struct ISwiwRect : ISwiwObject
{
	SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_InitParam);

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
// ISwiwCreateViewParam
//

struct ISwiwCreateViewParam : ISwiwObject
{
	SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_CreateViewParam);

	virtual ISwiwRect* GetRect() const = 0;
	virtual void SetRect(const ISwiwRect* rect) = 0;

	virtual const wchar_t* GetUri() const = 0;
	virtual void SetUri(const wchar_t* uri) = 0;
};


#else // pure c
typedef struct ISwiwObject ISwiwObject;
typedef struct ISwiwAPICallResult ISwiwAPICallResult;
typedef struct ISwiwInitParam ISwiwInitParam;
typedef struct ISwiwCreateViewParam ISwiwCreateViewParam;

#endif // __cplusplus

// ============================================================
//  Callbacks
// ============================================================

typedef void(CXX_CDECL* SwiwCallbackFn)(void* self, const ISwiwAPICallResult* res, const ISwiwObject* payload);
