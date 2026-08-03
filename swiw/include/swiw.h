#pragma once


#ifdef __cplusplus
extern "C"
{
#endif

	void SWIW_Init();

	void SWIW_Shutdown();

	void SWIW_Create();

	void SWIW_GetVersion(wchar_t* outVersion);

#ifdef __cplusplus
}
#endif
