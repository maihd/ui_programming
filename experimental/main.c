#include <math.h>
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
    HWND hWnd = CreateWindowA("UIExprWindow", "UI Experimental", WS_POPUPWINDOW | WS_VISIBLE, -1, -1, 800, 600, NULL, NULL, NULL, NULL);
    if (!hWnd)
    {
        printf("UIExprCreateWindow failed to create window\n");
    }

    printf("UIExprCreateWindow end\n");
}


CALLBACK LRESULT UIExprWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int mouseLeftDown = 0;
    static int prevXPos = -1;
    static int prevYPos = -1;

    switch (uMsg)
    {
    case WM_MOUSEMOVE:
        {
            const int xPos = GET_X_LPARAM(lParam);
            const int yPos = GET_Y_LPARAM(lParam);

            if (prevXPos < 0 || prevYPos < 0)
            {
                prevXPos = xPos;
                prevYPos = yPos;
                return 0;
            }

            if (mouseLeftDown)
            {
                const int dx = (xPos - prevXPos);
                const int dy = (yPos - prevYPos);
                if (abs(dx) < 20 || abs(dy) < 20)
                {
                    return 0;
                }

                RECT rect;
                if (!GetWindowRect(hWnd, &rect))
                {
                    return 0;
                }

                const int newXPos = rect.left + dx;
                const int newYPos = rect.top + dy;

                SetWindowPos(hWnd, NULL, newXPos, newYPos, 0, 0, SWP_NOSIZE);
            }

            prevXPos = xPos;
            prevYPos = yPos;

            return 0;
        }

    case WM_LBUTTONUP:
        mouseLeftDown = 0;
        break;

    case WM_LBUTTONDOWN:
        mouseLeftDown = 1;
        break;

    case WM_CREATE:
        break;

//     case WM_NCCALCSIZE:
//         return 0;

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


