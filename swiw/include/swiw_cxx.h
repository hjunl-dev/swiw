/*
 * file: swiw_cxx.h
 *
 * C++-only convenience layer. Header-only, compiled by the caller, not part of
 * the exported ABI. Optional: viewui_api.h / viewui_flat_api.h are usable on
 * their own.
 */

#pragma once

#ifndef __cplusplus
#error "viewui_cpp.h is C++ only. Use viewui_api.h / viewui_flat_api.h from C."
#endif

#include "swiw.h"


 // ============================================================
 //  Callback binder
 // ============================================================

template<typename TOwner, typename TPayload>
class SwiwCallbackObject
{
public:
	using MemberFn = void(TOwner::*)(const ISwiwAPICallResult* res, const TPayload* payload);

	SwiwCallbackObject() :
		owner_(nullptr), fn_(nullptr), event_id_(0), registered_(false),
	{
	}

	SwiwCallbackObject(TOwner* owner, MemberFn fn, void* user_data = nullptr) :
		owner_(nullptr), fn_(nullptr), event_id_(0), registered_(false),
	{
		Bind(owner, fn, user_data);
	}

		~SwiwCallbackObject()
	{
		UnBind();
	}

	bool Bind(TOwner* owner, MemberFn fn, void* user_data)
	{
		UnBind();

		if (owner == nullptr || fn == nullptr)
			return;

		owner_ = owner;
		fn_ = fn;
		event_id_ = static_cast<int32_t>(TPayload::k_eStaticTypeKind);

		ISwiwAPICallResult* result = SWIW_RegisterCallback(this, &Trampoline, event_id_, user_data);
		registered_ = result->IsOk();

		if (!result->IsOk())
		{
			owner_ = nullptr;
			fn_ = nullptr;
		}
		return registered_;
	}

	void UnBind()
	{
		if (registered_)
		{
			SWIW_UnregisterCallback(this, event_id_);
			registered_ = false;
		}
		owner_ = nullptr;
		fn_ = nullptr;
	}

	bool IsRegistered() const { return _registered; }

	SwiwCallbackObject(const SwiwCallbackObject&) = delete;
	SwiwCallbackObject& operator=(const SwiwCallbackObject&) = delete;
	SwiwCallbackObject(SwiwCallbackObject&&) = delete;
	SwiwCallbackObject& operator=(SwiwCallbackObject&&) = delete;

private:
	static void CXX_CDECL Trampoline(void* self, const ISwiwAPICallResult* res, const ISwiwObject* payload)
	{
		SwiwCallbackObject* obj = static_cast<SwiwCallbackObject*>(self);
		if (obj == nullptr || obj->owner_ == nullptr || obj->fn_ == nullptr)
			return;

		const TPayload* typed = nullptr;
		if (payload != nullptr && payload->GetType() == static_cast<int32_t>(TPayload::k_eStaticTypeKind))
			typed = static_cast<TPayload*>(payload);

		(obj->owner_->*obj->fn_)(res, typed);
	}

	TOwner* owner_;
	MemberFn fn_;
	int32_t event_id_;
	bool registered_;
};

#define SWIW_CALLBACK(TOwner, FnName, TPayload)			\
	SwiwCallbackObject<TOwner, TPayload> cb_##FnName_;	\
	void FnName(const ISwiwAPICallResult* res,			\
				const TPayload* payload)

// ============================================================
//  RAII Guard
// ============================================================
