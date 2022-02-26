#pragma once

#include <stdarg.h>
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#define STRICT 1
#include <Windows.h>
#include <strsafe.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
/*
this means we need to debug from Visual Studio (or VS Code using inner
terminal), to actually see the debug output which in turn means we do not need
to build console testing apps which in turn is moving us closer to real life
runtimes inside services or win32 desktop apps or some such thing
*/
__inline void DBJ_DBG_PRINT(const char* format_, ...) {
  char buffy[1024] = {0};  // magical number; not exemplary
  va_list args = {0};
  va_start(args, format_);
  int nBuf = _vsnprintf_s(buffy, 1024, 1024, format_, args);
  if (nBuf > -1)
    OutputDebugStringA(buffy);
  else
    OutputDebugStringA(__FILE__ " OutputDebugStringA buffer overflow\n");
  va_end(args);
}
#else
#define DBJ_DBG_PRINT(format_, ...) ((void)0)
#endif

// TERROR == Terminating Errpr
#define DBJ_TERROR(format_, ...)         \
  do {                                   \
    DBJ_DBG_PRINT(format_, __VA_ARGS__); \
    exit(1 /*EXIT_FAILURE*/);            \
  } while (0);

#pragma region cruft

#define DBJ_APPBUFFER_LEN 1024

#ifndef DBJ_APPNAME_
#define DBJ_APPNAME_ "MTR Queue Example  "
#endif

#ifdef _DEBUG
#define DBJ_APPNAME DBJ_APPNAME_ "DEBUG build"
#else
#define DBJ_APPNAME DBJ_APPNAME_ "RELEASE build"
#endif

/*-----------------------------------------------------------------
 * must use the result immediately
 */
__inline LPSTR last_win_error_(void) {
  LPSTR lpMsgBuf = 0;
  DWORD dw = GetLastError();

  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                 (LPSTR)&lpMsgBuf, 0, NULL);

  static CHAR lpDisplayBuf[DBJ_APPBUFFER_LEN] = {0};

  (void)StringCchPrintfA(lpDisplayBuf, DBJ_APPBUFFER_LEN, "Last error (%d): %s",
                         dw, lpMsgBuf);

  LocalFree(lpMsgBuf);
  return lpDisplayBuf;
}
// print with last win32 error message added
__inline void WINPRIN(const char* format_, ...) {
  char buffy[DBJ_APPBUFFER_LEN] = {0};  // magical number; not exemplary code
  va_list args = {0};
  va_start(args, format_);
  int nBuf = _vsnprintf_s(buffy, DBJ_APPBUFFER_LEN, DBJ_APPBUFFER_LEN, format_, args);
  if (nBuf < 1) {
    OutputDebugStringA(__FILE__ " : buffer overflow\n");
    (void)MessageBoxA(NULL, (__FILE__ " : buffer overflow\n"), "Error", MB_OK);
    va_end(args);
    return;
  }
  va_end(args);

  // add the last error full message
  HRESULT res_ =
      StringCchPrintfA(buffy, DBJ_APPBUFFER_LEN, "%s\n\n%s", buffy, last_win_error_());

  if (res_ != S_OK) {
    OutputDebugStringA(__FILE__ " : buffer overflow\n");
    (void)MessageBoxA(NULL, (__FILE__ " : buffer overflow\n"), "Error", MB_OK);
    return;
  }
  OutputDebugStringA(buffy);
  (void)MessageBoxA(NULL, (LPCSTR)buffy, DBJ_APPNAME, MB_OK);
}
#pragma endregion  // cruft

#ifdef __cplusplus
}// extern "C" {
#endif
