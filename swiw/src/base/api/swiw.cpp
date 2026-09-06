#include "include/swiw.h"

#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "Version.lib")

#ifdef __cplusplus
extern "C" {
#endif

void SWIW_Init(const ISwiwInitParam* param) {}

void SWIW_Shutdown() {}

ISwiwObject* SWIW_CreateParam(int32_t param_kind) {
  ISwiwObject* param = nullptr;

  switch (static_cast<ESwiwTypeKind>(param_kind)) {
    case k_ESwiwTypeKind_InitParam: {
      break;
    }
    case k_ESwiwTypeKind_CreateWebViewParam: {
      break;
    }
    case k_ESwiwTypeKind_CreatePopupParam: {
      break;
    }
  }

  return param;
}

ISwiwAPICallResult* SWIW_RegisterCallback(void* self, SwiwCallbackFn callback,
                                          int32_t eventId, void* userData) {
  return nullptr;
}

void SWIW_UnregisterCallback(void* self, int32_t eventId) {}

void SWIW_CreateWebView(const ISwiwCreateWebViewParam* param) {}

void SWIW_CreatePopup(const ISwiwCreatePopupParam* param) {}

void SWIW_GetVersion(wchar_t* outVersion) {
  if (!outVersion) return;
  outVersion[0] = L'\0';

  HMODULE hModule = NULL;

  ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&SWIW_GetVersion, &hModule);

  if (hModule != NULL) {
    WCHAR path[MAX_PATH];
    GetModuleFileName(hModule, path, MAX_PATH);

    DWORD verHandle = 0;
    DWORD verSize = GetFileVersionInfoSize(path, &verHandle);

    if (verSize > 0) {
      LPVOID verData = malloc(verSize);
      if (GetFileVersionInfo(path, verHandle, verSize, verData)) {
        UINT size = 0;
        LPVOID lpBuffer = NULL;

        if (VerQueryValue(verData, L"\\", &lpBuffer, &size) && size > 0) {
          VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
          if (verInfo->dwSignature == 0xfeef04bd) {
            swprintf_s(outVersion, 64, L"%d.%d.%d.%d",
                       (verInfo->dwFileVersionMS >> 16) & 0xffff,
                       (verInfo->dwFileVersionMS >> 0) & 0xffff,
                       (verInfo->dwFileVersionLS >> 16) & 0xffff,
                       (verInfo->dwFileVersionLS >> 0) & 0xffff);
          }
        }
      }
      free(verData);
    }
  }
}

#ifdef __cplusplus
}
#endif
