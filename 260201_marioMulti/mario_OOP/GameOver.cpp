#include "GameOver.hpp"
#include <windows.h>

#define ID_BTN_CLOSE 1001

static LRESULT CALLBACK GameOverWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BTN_CLOSE) {
            DestroyWindow(hWnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hWnd, message, wParam, lParam);
    }
    return 0;
}

void GameOver::show() {
    HINSTANCE hInst = GetModuleHandleA(NULL);
    const char CLASS_NAME[] = "GameOverWndClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = GameOverWndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);

    RegisterClassA(&wc);

    //создание окна
    HWND hWnd = CreateWindowExA(
        WS_EX_DLGMODALFRAME,
        CLASS_NAME,
        "GAME OVER",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 360, 160,
        NULL, NULL, hInst, NULL);

    if (!hWnd) return;

    CreateWindowA("STATIC", "YOU HAVE COMPLETED ALL LEVELS!",
                  WS_CHILD | WS_VISIBLE | SS_CENTER,
                  10, 10, 340, 60,
                  hWnd, NULL, hInst, NULL);

    CreateWindowA("BUTTON", "Close",
                  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                  130, 80, 100, 30,
                  hWnd, (HMENU)ID_BTN_CLOSE, hInst, NULL);

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    //убедиться, что окно закрыто, прежде чем выйти из игры
    exit(0);
}
