HWND __fastcall AntiDebugger(__int64 instance)
{
  _QWORD *scue_instance; // rbx
  HANDLE *scue_process; // rcx
  HMODULE kernel32Base; // rax
  HMODULE kernel32BaseBuffer; // rbx
  __int64 (*IsDebuggerPresentAddr)(void); // rax
  HWND result; // rax

  scue_instance = (_QWORD *)instance;
  scue_process = (HANDLE *)(instance + 48);
  if ( !*scue_process || !(unsigned __int8)WaitForSingleObjectFunc(scue_process) ) // waiting for the handle to the ac
    SCUE_Check(scue_instance); // check if scue can be handled
  kernel32Base = LoadLibraryExW(L"kernel32.dll", 0i64, 0); // get kernel 32 base
  kernel32BaseBuffer = kernel32Base;
  IsDebuggerPresentAddr = (__int64 (*)(void))GetProcAddress(kernel32Base, "IsDebuggerPresent"); // export isdebuggerpresent
  if ( IsDebuggerPresentAddr && IsDebuggerPresentAddr() ) // check if a debugger is present
  {
    FreeLibrary(kernel32BaseBuffer); // free the base
    result = (HWND)RequestExit(0); // request exit from UE4 function
  }
  else
  {
    FreeLibrary(kernel32BaseBuffer);
    if ( OpenFileMappingW(6u, 0, L"CEHYPERSCANSETTINGS") // open a handle to a object 
      || FindWindowA("WinDbgFrameClass", 0i64) // check forst windbg
      || FindWindowA("WinDbgFrameClass", 0i64)
      || FindWindowA("OLLYDBG", 0i64) // check for ollydbg/x64dbg & related classes
      || (result = FindWindowA("Window", 0i64)) != 0i64 )
    {
      result = (HWND)RequestExit(0);
    }
  }
  return result;
}
