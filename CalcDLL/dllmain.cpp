// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include "CCalculator.h"

HINSTANCE g_hThisDLL;
CCalculator g_calcObj;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    g_hThisDLL = hModule;

    return TRUE;
}

extern "C" __declspec(dllexport) void SetInput(const TCHAR *input)
{
    g_calcObj.SetInput(input);
}

extern "C" __declspec(dllexport) bool CheckSyntax()
{
     return g_calcObj.IsSyntaxCorrect();
}

extern "C" __declspec(dllexport) long double Compute()
{
    return g_calcObj.Compute();
}
