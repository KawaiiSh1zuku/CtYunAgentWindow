#include <iostream>
#include <windows.h>
#include <string.h>
#include <tchar.h>
#pragma comment(lib, "user32.lib")

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
    char className[256];
    GetClassNameA(hwnd, className, sizeof(className));

    std::cout << "Child Window: " << className << std::endl;

    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);

    std::cout << "Client Area Resolution: " << clientRect.right - clientRect.left
        << " x " << clientRect.bottom - clientRect.top << std::endl;

    std::cout << "Window Resolution: " << windowRect.right - windowRect.left
        << " x " << windowRect.bottom - windowRect.top << std::endl;

    if (windowRect.right - windowRect.left < screenWidth && windowRect.bottom - windowRect.top < screenHeight) {
        std::cout << "You are just the window I'm looking for!" << std::endl;
        HWND hd = reinterpret_cast<HWND>(lParam);
        if (IsWindowVisible(hd)) {
            ShowWindow(hd, SW_HIDE);
            std::cout << "Hid" << std::endl;
        }
        else {
            ShowWindow(hd, SW_SHOW);
            std::cout << "Shown" << std::endl;
        }
        return false;
    }
    return true;
}

int main(int argc, _TCHAR* argv[])
{
    HWND hd = GetDesktopWindow();

    hd = GetWindow(hd, GW_CHILD);
    char s[200] = { 0 };

    while (hd != NULL)
    {
        memset(s, 0, 200);
        GetWindowText(hd, s, 200);
        if (strstr(s,"CtyunClouddeskUniversal"))
        {
            EnumChildWindows(hd, EnumChildProc, reinterpret_cast<LPARAM>(hd));
        }
        hd = GetNextWindow(hd, GW_HWNDNEXT);
    }

    return 0;
}
