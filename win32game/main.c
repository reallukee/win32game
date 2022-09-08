#include <stdlib.h>
#include <time.h>
#include <windows.h>

HINSTANCE hInst;

int playerX = 0;
int playerY = 0;
int foodX = 0;
int foodY = 0;

int APIENTRY        WinMain(HINSTANCE, HINSTANCE, LPWSTR, int);
ATOM                MyRegisterClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    srand(time(0));

    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = L"Game";
    wcex.hIconSm        = NULL;

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindow(
        L"Game",
        L"Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        516,
        539,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        playerX = rand() % 10;
        playerY = rand() % 10;

        while (foodX == playerX)
        {
            foodX = rand() % 10;
        }

        while (foodY == playerY)
        {
            foodY = rand() % 10;
        }

        long wndLong = GetWindowLong(hWnd, GWL_STYLE);
        SetWindowLong(hWnd, GWL_STYLE, wndLong & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);

        break;

    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* mmi = (MINMAXINFO*)lParam;

        mmi->ptMinTrackSize.x = 516;
        mmi->ptMinTrackSize.y = 539;
        mmi->ptMaxTrackSize.x = 516;
        mmi->ptMaxTrackSize.y = 539;
    }

    break;

    case WM_DESTROY:
        PostQuitMessage(0);

        break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rect;

        FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 255, 0)));

        rect.left   = playerX * 50;
        rect.top    = playerY * 50;
        rect.right  = playerX * 50 + 50;
        rect.bottom = playerY * 50 + 50;
        FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));

        rect.left   = foodX * 50;
        rect.top    = foodY * 50;
        rect.right  = foodX * 50 + 50;
        rect.bottom = foodY * 50 + 50;
        FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 255)));

        EndPaint(hWnd, &ps);

        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'W':
        case 'w':
        case VK_UP:
            if (playerY - 1 >= 0)
            {
                playerY--;
            }
            else
            {
                playerY = 9;
            }

            break;

        case 'S':
        case 's':
        case VK_DOWN:
            if (playerY + 1 <= 9)
            {
                playerY++;
            }
            else
            {
                playerY = 0;
            }

            break;

        case 'A':
        case 'a':
        case VK_LEFT:
            if (playerX - 1 >= 0)
            {
                playerX--;
            }
            else
            {
                playerX = 9;
            }

            break;

        case 'D':
        case 'd':
        case VK_RIGHT:
            if (playerX + 1 <= 9)
            {
                playerX++;
            }
            else
            {
                playerX = 0;
            }

            break;

        default:
            break;
        }

        InvalidateRect(hWnd, NULL, FALSE);

        if (playerX == foodX && playerY == foodY)
        {
            while (foodX == playerX)
            {
                foodX = rand() % 10;
            }

            while (foodY == playerY)
            {
                foodY = rand() % 10;
            }
        }

        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
