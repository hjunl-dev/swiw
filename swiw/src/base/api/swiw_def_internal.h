/*
 * file: swiw_def_internal.h
 *
 * Header for the internal implementation (CRTP Impl) of the SWIW interface.
 * Interface-to-Implementation inheritance structure.
 *
 * ISwiwObject
 *		↑
 * ISwiwXXX (pure virtual interface)
 *		↑
 * SwiwObjectBase<Self, ISwiwXXX>
 *		↑
 * SwiwXXXImpl
 */

#pragma once
#include <format>
#include <string>
#include <type_traits>

#include "include/swiw_def.h"

// ============================================================
//  Type impls
// ============================================================

//
// SwiwObjectBase (CRTP)
//

template <typename TSelf, typename TInterface>
struct SwiwObjectBase : public TInterface {
  int32_t GetType() const override { return type_; }
  bool GetOwnership() const override { return ownership_; }
  void Release() override {
    if (ownership_) {
      delete static_cast<TSelf*>(this);
    }
  }
  void* Query(int32_t id) const override {
    (void)id;
    return nullptr;
  }
  const wchar_t* ToString() const override {
    str_cache_ = static_cast<const TSelf*>(this)->ToStringImpl();
    return str_cache_.c_str();
  }
  template <typename T>
  T* CastTo() {
    static_assert(std::is_base_of_v<SwiwObjectBase, T>,
                  "T must derive from this base");
    if (type_ == static_cast<int32_t>(T::k_eStaticTypeKind)) {
      return static_cast<T*>(this);
    }
    return nullptr;
  }
  void SetOwnership(bool owned) { ownership_ = owned; }
  static TSelf* Create(bool ownership = false) {
    auto* p = new TSelf();
    p->SetOwnership(ownership);
    return p;
  }

 protected:
  SwiwObjectBase()
      : type_(static_cast<int32_t>(TInterface::k_eStaticTypeKind)) {}
  ~SwiwObjectBase() = default;

  std::wstring ToStringImpl() const {
    return std::format(L"SwiwObject{{type={}, owned={}, this={}}}", type_,
                       ownership_, static_cast<const void*>(this));
  }

  int32_t type_ = k_ESwiwTypeKind_Invalid;
  bool ownership_ = false;

 private:
  mutable std::wstring str_cache_;
};

//
// SwiwAPICallResultImpl
//

struct SwiwAPICallResultImpl final
    : SwiwObjectBase<SwiwAPICallResultImpl, ISwiwAPICallResult> {
  bool IsOk() const override { return error_code_ == 0; }
  int32_t GetErrorCode() const override { return error_code_; }
  int32_t GetApiCode() const override { return api_code_; }
  const wchar_t* GetErrorMsg() const override { return error_msg_.c_str(); }

  void SetErrorCode(int32_t code) { error_code_ = code; }
  void SetApiCode(int32_t code) { api_code_ = code; }
  void SetErrorMsg(const wchar_t* msg) { error_msg_ = msg ? msg : L""; }

  std::wstring ToStringImpl() const {
    return std::format(L"SwiwAPICallResult{{api={}, err={}, msg=\"{}\"}}",
                       api_code_, error_code_, error_msg_);
  }

 private:
  int32_t error_code_ = 0;
  int32_t api_code_ = 0;
  std::wstring error_msg_;
};

//
// SwiwInitParamImpl
//
struct SwiwInitParamImpl final
    : SwiwObjectBase<SwiwInitParamImpl, ISwiwInitParam> {
  const wchar_t* GetUdfPath() const override { return udf_path_.c_str(); }
  void SetUdfPath(const wchar_t* udf_path) override {
    udf_path_ = udf_path ? udf_path : L"";
  }

  std::wstring ToStringImpl() const {
    return std::format(L"SwiwInitParam{{udfPath=\"{}\"}}", udf_path_);
  }

 private:
  std::wstring udf_path_;
};

//
// SwiwRectImpl
//
struct SwiwRectImpl final : SwiwObjectBase<SwiwRectImpl, ISwiwRect> {
  int32_t GetX() const override { return x_; }
  void SetX(int32_t x) override { x_ = x; }
  int32_t GetY() const override { return y_; }
  void SetY(int32_t y) override { y_ = y; }
  int32_t GetWidth() const override { return width_; }
  void SetWidth(int32_t width) override { width_ = width; }
  int32_t GetHeight() const override { return height_; }
  void SetHeight(int32_t height) override { height_ = height; }

  std::wstring ToStringImpl() const {
    return std::format(L"SwiwRect{{x={}, y={}, w={}, h={}}}", x_, y_, width_,
                       height_);
  }

 private:
  int32_t x_ = 0;
  int32_t y_ = 0;
  int32_t width_ = 0;
  int32_t height_ = 0;
};

//
// SwiwCreateWebViewParamImpl
//
struct SwiwCreateWebViewParamImpl final
    : SwiwObjectBase<SwiwCreateWebViewParamImpl, ISwiwCreateWebViewParam> {
  ISwiwRect* GetRect() override { return &rect_; }
  void SetRect(const ISwiwRect* rect) override {
    if (rect == nullptr) return;
    rect_.SetX(rect->GetX());
    rect_.SetY(rect->GetY());
    rect_.SetWidth(rect->GetWidth());
    rect_.SetHeight(rect->GetHeight());
  }

  const wchar_t* GetUri() const override { return uri_.c_str(); }
  void SetUri(const wchar_t* uri) override { uri_ = uri ? uri : L""; }

  std::wstring ToStringImpl() const {
    return std::format(L"SwiwCreateWebViewParam{{uri=\"{}\", rect={}}}", uri_,
                       rect_.ToStringImpl());
  }

 private:
  SwiwRectImpl rect_;
  std::wstring uri_;
};

//
// SwiwCreatePopupParamImpl
//

struct SwiwCreatePopupParamImpl final
    : SwiwObjectBase<SwiwCreatePopupParamImpl, ISwiwCreatePopupParam> {
  ISwiwRect* GetRect() override { return &rect_; }
  void SetRect(const ISwiwRect* rect) override {
    if (rect == nullptr) return;
    rect_.SetX(rect->GetX());
    rect_.SetY(rect->GetY());
    rect_.SetWidth(rect->GetWidth());
    rect_.SetHeight(rect->GetHeight());
  }

  std::wstring ToStringImpl() const {
    return std::format(L"SwiwCreatePopupParam{{rect={}}}",
                       rect_.ToStringImpl());
  }

 private:
  SwiwRectImpl rect_;
};
