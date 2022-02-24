// (c) 2022 by dbj at dbj fpt org
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern int mtr_queue_example(int argc, char *argv[]);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  return mtr_queue_example(0, (char **)0);
}
