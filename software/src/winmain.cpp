#ifdef _WIN32
#include <windows.h>

int main();

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int nCmdShow)
{
    return main();
}
#endif
