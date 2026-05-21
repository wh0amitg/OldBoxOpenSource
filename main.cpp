#include <cstdio>
#include <string>
#include <iostream>
#include <windows.h>
#include "Minhook.h"

#pragma comment(linker, "/NODEFAULTLIB:LIBCMT")

// --- Прокси функции (Экспорт оригинальной version.dll) ---
#define PROXY_OUT(func) __pragma(comment(linker, "/export:" #func "=My" #func))
PROXY_OUT(GetFileVersionInfoA) PROXY_OUT(GetFileVersionInfoByHandle) PROXY_OUT(GetFileVersionInfoExA) PROXY_OUT(GetFileVersionInfoExW) PROXY_OUT(GetFileVersionInfoSizeA) PROXY_OUT(GetFileVersionInfoSizeExA) PROXY_OUT(GetFileVersionInfoSizeExW) PROXY_OUT(GetFileVersionInfoSizeW) PROXY_OUT(GetFileVersionInfoW) PROXY_OUT(VerFindFileA) PROXY_OUT(VerFindFileW) PROXY_OUT(VerInstallFileA) PROXY_OUT(VerInstallFileW) PROXY_OUT(VerLanguageNameA) PROXY_OUT(VerLanguageNameW) PROXY_OUT(VerQueryValueA) PROXY_OUT(VerQueryValueW)

BOOL(WINAPI* o_GetFileVersionInfoA)(LPCSTR, DWORD, DWORD, LPVOID) = nullptr;
BOOL(WINAPI* o_GetFileVersionInfoByHandle)(DWORD, HANDLE, LPVOID, DWORD) = nullptr;
BOOL(WINAPI* o_GetFileVersionInfoExA)(DWORD, LPCSTR, DWORD, DWORD, LPVOID) = nullptr;
BOOL(WINAPI* o_GetFileVersionInfoExW)(DWORD, LPCWSTR, DWORD, DWORD, LPVOID) = nullptr;
DWORD(WINAPI* o_GetFileVersionInfoSizeA)(LPCSTR, LPDWORD) = nullptr;
DWORD(WINAPI* o_GetFileVersionInfoSizeExA)(DWORD, LPCSTR, LPDWORD) = nullptr;
DWORD(WINAPI* o_GetFileVersionInfoSizeExW)(DWORD, LPCWSTR, LPDWORD) = nullptr;
DWORD(WINAPI* o_GetFileVersionInfoSizeW)(LPCWSTR, LPDWORD) = nullptr;
BOOL(WINAPI* o_GetFileVersionInfoW)(LPCWSTR, DWORD, DWORD, LPVOID) = nullptr;
DWORD(WINAPI* o_VerFindFileA)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPSTR, PUINT, LPSTR, PUINT) = nullptr;
DWORD(WINAPI* o_VerFindFileW)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, PUINT, LPWSTR, PUINT) = nullptr;
DWORD(WINAPI* o_VerInstallFileA)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPSTR, PUINT) = nullptr;
DWORD(WINAPI* o_VerInstallFileW)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPSTR, PUINT) = nullptr;
DWORD(WINAPI* o_VerLanguageNameA)(DWORD, LPSTR, DWORD) = nullptr;
DWORD(WINAPI* o_VerLanguageNameW)(DWORD, LPWSTR, DWORD) = nullptr;
BOOL(WINAPI* o_VerQueryValueA)(LPCVOID, LPCSTR, LPVOID*, PUINT) = nullptr;
BOOL(WINAPI* o_VerQueryValueW)(LPCVOID, LPCWSTR, LPVOID*, PUINT) = nullptr;

extern "C" {
    BOOL WINAPI MyGetFileVersionInfoA(LPCSTR l, DWORD d1, DWORD d2, LPVOID p) { return o_GetFileVersionInfoA ? o_GetFileVersionInfoA(l, d1, d2, p) : FALSE; }
    BOOL WINAPI MyGetFileVersionInfoByHandle(DWORD d1, HANDLE h, LPVOID p, DWORD d2) { return o_GetFileVersionInfoByHandle ? o_GetFileVersionInfoByHandle(d1, h, p, d2) : FALSE; }
    BOOL WINAPI MyGetFileVersionInfoExA(DWORD d1, LPCSTR l, DWORD d2, DWORD d3, LPVOID p) { return o_GetFileVersionInfoExA ? o_GetFileVersionInfoExA(d1, l, d2, d3, p) : FALSE; }
    BOOL WINAPI MyGetFileVersionInfoExW(DWORD d1, LPCWSTR l, DWORD d2, DWORD d3, LPVOID p) { return o_GetFileVersionInfoExW ? o_GetFileVersionInfoExW(d1, l, d2, d3, p) : FALSE; }
    DWORD WINAPI MyGetFileVersionInfoSizeA(LPCSTR l, LPDWORD p) { return o_GetFileVersionInfoSizeA ? o_GetFileVersionInfoSizeA(l, p) : 0; }
    DWORD WINAPI MyGetFileVersionInfoSizeExA(DWORD d, LPCSTR l, LPDWORD p) { return o_GetFileVersionInfoSizeExA ? o_GetFileVersionInfoSizeExA(d, l, p) : 0; }
    DWORD WINAPI MyGetFileVersionInfoSizeExW(DWORD d, LPCWSTR l, LPDWORD p) { return o_GetFileVersionInfoSizeExW ? o_GetFileVersionInfoSizeExW(d, l, p) : 0; }
    DWORD WINAPI MyGetFileVersionInfoSizeW(LPCWSTR l, LPDWORD p) { return o_GetFileVersionInfoSizeW ? o_GetFileVersionInfoSizeW(l, p) : 0; }
    BOOL WINAPI MyGetFileVersionInfoW(LPCWSTR l, DWORD d1, DWORD d2, LPVOID p) { return o_GetFileVersionInfoW ? o_GetFileVersionInfoW(l, d1, d2, p) : FALSE; }
    DWORD WINAPI MyVerFindFileA(DWORD d, LPCSTR l1, LPCSTR l2, LPCSTR l3, LPSTR l4, PUINT p1, LPSTR l5, PUINT p2) { return o_VerFindFileA ? o_VerFindFileA(d, l1, l2, l3, l4, p1, l5, p2) : 0; }
    DWORD WINAPI MyVerFindFileW(DWORD d, LPCWSTR l1, LPCWSTR l2, LPCWSTR l3, LPWSTR l4, PUINT p1, LPWSTR l5, PUINT p2) { return o_VerFindFileW ? o_VerFindFileW(d, l1, l2, l3, l4, p1, l5, p2) : 0; }
    DWORD WINAPI MyVerInstallFileA(DWORD d, LPCSTR l1, LPCSTR l2, LPCSTR l3, LPCSTR l4, LPCSTR l5, LPSTR l6, PUINT p) { return o_VerInstallFileA ? o_VerInstallFileA(d, l1, l2, l3, l4, l5, l6, p) : 0; }
    DWORD WINAPI MyVerInstallFileW(DWORD d, LPCWSTR l1, LPCWSTR l2, LPCWSTR l3, LPCWSTR l4, LPCWSTR l5, LPSTR l6, PUINT p) { return o_VerInstallFileW ? o_VerInstallFileW(d, l1, l2, l3, l4, l5, l6, p) : 0; }
    DWORD WINAPI MyVerLanguageNameA(DWORD d, LPSTR l, DWORD d2) { return o_VerLanguageNameA ? o_VerLanguageNameA(d, l, d2) : 0; }
    DWORD WINAPI MyVerLanguageNameW(DWORD d, LPWSTR l, DWORD d2) { return o_VerLanguageNameW ? o_VerLanguageNameW(d, l, d2) : 0; }
    BOOL WINAPI MyVerQueryValueA(LPCVOID p, LPCSTR l, LPVOID* lp, PUINT pu) { return o_VerQueryValueA ? o_VerQueryValueA(p, l, lp, pu) : FALSE; }
    BOOL WINAPI MyVerQueryValueW(LPCVOID p, LPCWSTR l, LPVOID* lp, PUINT pu) { return o_VerQueryValueW ? o_VerQueryValueW(p, l, lp, pu) : FALSE; }
}

void SetupProxy() {
    char sysPath[MAX_PATH]; GetSystemDirectoryA(sysPath, MAX_PATH);
    HMODULE hReal = LoadLibraryA((std::string(sysPath) + "\\version.dll").c_str());
    if (!hReal) return;
    o_GetFileVersionInfoA = (decltype(o_GetFileVersionInfoA))GetProcAddress(hReal, "GetFileVersionInfoA");
    o_GetFileVersionInfoByHandle = (decltype(o_GetFileVersionInfoByHandle))GetProcAddress(hReal, "GetFileVersionInfoByHandle");
    o_GetFileVersionInfoExA = (decltype(o_GetFileVersionInfoExA))GetProcAddress(hReal, "GetFileVersionInfoExA");
    o_GetFileVersionInfoExW = (decltype(o_GetFileVersionInfoExW))GetProcAddress(hReal, "GetFileVersionInfoExW");
    o_GetFileVersionInfoSizeA = (decltype(o_GetFileVersionInfoSizeA))GetProcAddress(hReal, "GetFileVersionInfoSizeA");
    o_GetFileVersionInfoSizeExA = (decltype(o_GetFileVersionInfoSizeExA))GetProcAddress(hReal, "GetFileVersionInfoSizeExA");
    o_GetFileVersionInfoSizeExW = (decltype(o_GetFileVersionInfoSizeExW))GetProcAddress(hReal, "GetFileVersionInfoSizeExW");
    o_GetFileVersionInfoSizeW = (decltype(o_GetFileVersionInfoSizeW))GetProcAddress(hReal, "GetFileVersionInfoSizeW");
    o_GetFileVersionInfoW = (decltype(o_GetFileVersionInfoW))GetProcAddress(hReal, "GetFileVersionInfoW");
    o_VerFindFileA = (decltype(o_VerFindFileA))GetProcAddress(hReal, "VerFindFileA");
    o_VerFindFileW = (decltype(o_VerFindFileW))GetProcAddress(hReal, "VerFindFileW");
    o_VerInstallFileA = (decltype(o_VerInstallFileA))GetProcAddress(hReal, "VerInstallFileA");
    o_VerInstallFileW = (decltype(o_VerInstallFileW))GetProcAddress(hReal, "VerInstallFileW");
    o_VerLanguageNameA = (decltype(o_VerLanguageNameA))GetProcAddress(hReal, "VerLanguageNameA");
    o_VerLanguageNameW = (decltype(o_VerLanguageNameW))GetProcAddress(hReal, "VerLanguageNameW");
    o_VerQueryValueA = (decltype(o_VerQueryValueA))GetProcAddress(hReal, "VerQueryValueA");
    o_VerQueryValueW = (decltype(o_VerQueryValueW))GetProcAddress(hReal, "VerQueryValueW");
}

uintptr_t GameAssembly = 0;
uintptr_t offset_ConnectUsingSettings = 0x0; // Photon.Pun.PhotonNetwork$$ConnectUsingSettings

struct Il2CppString { void* k; void* m; int32_t len; wchar_t chars[1]; };
Il2CppString* (*il2cpp_string_new)(const char*) = nullptr;

template <typename T> void WriteMem(uintptr_t addr, T val) {
    DWORD old; VirtualProtect((LPVOID)addr, sizeof(T), PAGE_EXECUTE_READWRITE, &old);
    *(T*)addr = val; VirtualProtect((LPVOID)addr, sizeof(T), old, &old);
}

typedef void(__fastcall* o_photon_hook_t)(void*, bool, void*);
o_photon_hook_t o_photon_hook = nullptr;

void __fastcall photon_hook(void* _appSettings, bool startInOfflineMode, void* mi) {
    if (_appSettings) {
        WriteMem<uintptr_t>((uintptr_t)_appSettings + 0x10, (uintptr_t)il2cpp_string_new("")); //APPID
        WriteMem<uintptr_t>((uintptr_t)_appSettings + 0x28, (uintptr_t)il2cpp_string_new("")); //APPIDVOICE
    }
    return o_photon_hook(_appSettings, startInOfflineMode, mi);
}

void Main() {
    while (!(GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll"))) Sleep(50);

    HMODULE hGA = (HMODULE)GameAssembly;
    il2cpp_string_new = (Il2CppString * (*)(const char*))GetProcAddress(hGA, "il2cpp_string_new");
    MH_Initialize();  

    uintptr_t targetAddr = GameAssembly + offset_ConnectUsingSettings;
    if (MH_CreateHook((LPVOID)targetAddr, (LPVOID)&photon_hook, (LPVOID*)&o_photon_hook) == MH_OK) {
        MH_EnableHook((LPVOID)targetAddr);
    }
}

BOOL APIENTRY DllMain(HMODULE hMod, DWORD reason, LPVOID lpRes) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hMod);
        SetupProxy();
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
    }
    return TRUE;
}
