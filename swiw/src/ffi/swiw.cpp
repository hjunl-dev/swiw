#include "swiw.h"

#include <stdio.h>
#include <windows.h>

#include "swiw_def_internal.h"

#pragma comment(lib, "Version.lib")

#ifdef __cplusplus
extern "C" {
#endif

void SWIW_Init(const ISwiwInitConfig* config) {}

void SWIW_Shutdown() {}

ISwiwObject* SWIW_CreateObject(int32_t type_kind) {
  ISwiwObject* config = nullptr;

  switch (static_cast<ESwiwTypeKind>(type_kind)) {
    case k_ESwiwTypeKind_Rect: {
      config = SwiwRectImpl::Create(true);
      break;
    }
    case k_ESwiwTypeKind_InitConfig: {
      config = SwiwInitConfigImpl::Create(true);
      break;
    }
    case k_ESwiwTypeKind_CreateWebViewConfig: {
      config = SwiwCreateWebViewConfigImpl::Create(true);
      break;
    }
    case k_ESwiwTypeKind_CreateWebUIConfig: {
      config = SwiwCreateWebUIConfigImpl::Create(true);
      break;
    }
  }
  return config;
}

ISwiwAPICallResult* SWIW_RegisterCallback(void* self, SwiwCallbackFn callback,
                                          int32_t eventId, void* userData) {
  return nullptr;
}

void SWIW_UnregisterCallback(void* self, int32_t eventId) {}

void SWIW_CreateWebView(const ISwiwCreateWebViewConfig* config) {
  // test code

  auto wndProc = [](HWND hWnd, UINT message, WPARAM wParam,
                    LPARAM lParam) -> LRESULT {
    switch (message) {
      case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
      } break;
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
  };

  auto hInstance = GetModuleHandleW(nullptr);

  // RegisterClass
  {
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TESTCLASS";
    wcex.hIconSm = nullptr;

    ::RegisterClassExW(&wcex);
  }

  // CreateWindow
  {
    auto rect = config->GetRect();

    HWND hWnd = ::CreateWindowExW(
        0, L"TESTCLASS", L"TESTTITLE", WS_OVERLAPPEDWINDOW, rect->GetX(),
        rect->GetY(), rect->GetWidth(), rect->GetHeight(), nullptr, nullptr,
        hInstance, nullptr);

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
  }
}

void SWIW_CreateWebUI(const ISwiwCreateWebUIConfig* config) {}

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
