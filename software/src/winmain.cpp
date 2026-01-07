#ifdef _WIN32
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main(int argc, char* argv[]); // forward declaration

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int nCmdShow)
{
    // Try to attach to parent console (PowerShell / CMD)
    bool consoleAttached = AttachConsole(ATTACH_PARENT_PROCESS) != 0;

    // Only redirect streams if console exists
    if (consoleAttached) {
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$",  "r", stdin);
    }

    // Convert LPSTR args to argc / argv
    std::vector<std::string> argv_strings;
    std::istringstream iss(args ? args : "");
    std::string token;
    while (iss >> token) {
        argv_strings.push_back(token);
    }

    // Build argv including program name
    std::vector<std::string> all_args;
    all_args.push_back("ROP.exe"); // argv[0]
    all_args.insert(all_args.end(), argv_strings.begin(), argv_strings.end());

    int argc = static_cast<int>(all_args.size());
    std::vector<char*> argv(argc);
    for (int i = 0; i < argc; ++i)
        argv[i] = all_args[i].data();

    try {
        return main(argc, argv.data());
    }
    catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "Exception", MB_OK | MB_ICONERROR);
        return 1;
    }
    catch (...) {
        MessageBoxA(nullptr, "Unknown exception occurred", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
}
#endif
