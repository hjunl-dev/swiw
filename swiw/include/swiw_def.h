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

typedef enum ESwiwTypeKind {
	k_ESwiwTypeKind_Invalid = -1,

	k_ESwiwTypeKind_ObjectBase = 0,
	k_ESwiwTypeKind_ApiCallResult = 0,

	k_ESwiwTypeKind_Max = 0x7fffffff,
} ESwiwTypeKind;



// ============================================================
//  Types
// ============================================================

#ifdef __cplusplus

#define SWIW_TYPE_KIND_DEF_STATIC(TypeKind) \
	static CXX_CONSTEXPR ESwiwTypeKind k_eStaticTypeKind = TypeKind

//
// ISwiwObjectBase
//

struct ISwiwObject
{
	SWIW_TYPE_KIND_DEF_STATIC(k_ESwiwTypeKind_Invalid);

	virtual int GetType() const = 0;
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


#else // pure c
typedef struct ISwiwObject ISwiwObject;
typedef struct ISwiwAPICallResult ISwiwAPICallResult;

#endif // __cplusplus


typedef void(CXX_CDECL* SwiwCallbackFn)(void* self, const ISwiwAPICallResult* res, const ISwiwObject* payload);
