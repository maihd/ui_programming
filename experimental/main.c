#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>


CALLBACK LRESULT UIExprWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


void UIExprCreateWindow(void)
{
    printf("UIExprCreateWindow begin\n");

    // Register window class
    printf("UIExprCreateWindow register window class\n");

    WNDCLASSA wndClass = {
        .style = 0,
        .lpszClassName = "UIExprWindow",
        .lpfnWndProc = UIExprWindowProc,
    };
    if (RegisterClassA(&wndClass))
    {
        printf("UIExprCreateWindow register class success\n");
    }
    else
    {
        printf("UIExprCreateWindow failed to register class\n");
    }

    // Create window object
    printf("UIExprCreateWindow create window object\n");
    HWND hWnd = CreateWindowA("UIExprWindow", "UI Experimental", WS_OVERLAPPEDWINDOW | WS_VISIBLE, -1, -1, 800, 600, NULL, NULL, NULL, NULL);
    if (!hWnd)
    {
        printf("UIExprCreateWindow failed to create window\n");
    }

    printf("UIExprCreateWindow end\n");
}


CALLBACK LRESULT UIExprWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int main()
{
    printf(
        "Hello world!\n"
        "This is a project for experimental some features that doesnot very needed for UI programming.\n"
        "But having is a plus.\n");
    printf("---------------------------------------------------------------------------------------------\n");

    UIExprCreateWindow();

    int done = 0;
    while (!done)
    {
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                done = 1;
                break;
            }
        }
    }

    return 0;
}

//! EOF


