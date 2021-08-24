//#define GAME or #define WIN

typedef HWND(__fastcall* t_AntiDebugger)(__int64 instance);
t_AntiDebugger sub_AntiDebugger = (t_AntiDebugger)((uintptr_t)memory::cached::GameBase + offsets::AntiCheatChecks);

typedef BOOL(__stdcall* t_IsDebuggerPresent)();
t_IsDebuggerPresent sub_IsDebuggerPresent = (t_IsDebuggerPresent)(GetProcAddress((HMODULE)memory::cached::Kernel32Base, xorstr_("IsDebuggerPresent")));

typedef HWND(__stdcall* t_FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName);
t_FindWindowA sub_FindWindowA = (t_FindWindowA)(GetProcAddress((HMODULE)memory::cached::User32Base, xorstr_("FindWindowA")));

HWND __fastcall hk_AntiDebugger(__int64 instance)
{
    HWND result; // rax
    result = { };

    return result;
}

BOOL hk_IsDebuggerPresent()
{
    BOOL result; // rbx
    result = { FALSE };

    return result;
}

HWND __stdcall hk_FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName)
{
    HWND result; // rax
    result = { };

    return result;
}

void InitHooks()
{
    memory::cached::GameBase = memory::ImageBase();
    memory::cached::Kernel32Base = memory::ModuleBase(xorstr_("kernel32.dll"));
    memory::cached::User32Base = memory::ModuleBase(xorstr_("user32.dll"));
    
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    
  // choose between game & win
#ifdef GAME
    DetourAttach(&(LPVOID&)sub_AntiDebugger, &hk_AntiDebugger); // by hooking game function
#else
    DetourAttach(&(LPVOID&)sub_IsDebuggerPresent, &hk_IsDebuggerPresent); // by hooking winapi function
    DetourAttach(&(LPVOID&)sub_FindWindowA, &hk_FindWindowA); // by hooking winapi function
#endif

    DetourTransactionCommit();
}
