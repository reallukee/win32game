#include "game.h"

void InitGame(HWND hWnd)
{
    unsigned seed = (unsigned)time(NULL);

    srand(seed);

    GeneratePlayer();

    GeneratePlayerFood();

    InvalidateRect(hWnd, NULL, TRUE);
}



void HandleInput(
    HWND hWnd,
    WPARAM wParam)
{
    switch (wParam)
    {
    case VK_UP:
    case 'W':
    case 'w':
        if (player.y - 1 >= 0)
        {
            player.y--;
        }
        else
        {
            player.y = ROWS_COUNT - 1;
        }

        break;

    case VK_DOWN:
    case 'S':
    case 's':
        if (player.y + 1 <= ROWS_COUNT - 1)
        {
            player.y++;
        }
        else
        {
            player.y = 0;
        }

        break;

    case VK_LEFT:
    case 'A':
    case 'a':
        if (player.x - 1 >= 0)
        {
            player.x--;
        }
        else
        {
            player.x = COLS_COUNT - 1;
        }

        break;

    case VK_RIGHT:
    case 'D':
    case 'd':
        if (player.x + 1 <= COLS_COUNT - 1)
        {
            player.x++;
        }
        else
        {
            player.x = 0;
        }

        break;

    default:
        break;
    }
}



void GeneratePlayer()
{
    player = (POINT){
        .x = rand() % COLS_COUNT,
        .y = rand() % ROWS_COUNT,
    };
}

void GeneratePlayerFood()
{
    BOOL check = TRUE;

    do
    {
        check = TRUE;

        playerFood = (POINT){
            .x = rand() % COLS_COUNT,
            .y = rand() % ROWS_COUNT,
        };

        if (player.x == playerFood.x && player.y == playerFood.y)
        {
            check = FALSE;
        }
    } while (!check);
}



void DrawField(HDC hDC)
{
    for (int y = 0; y < ROWS_COUNT; y++)
    {
        for (int x = 0; x < COLS_COUNT; x++)
        {
            RECT lprc = {
                x * CELL_WIDTH,
                y * CELL_HEIGHT,
                (x + 1) * CELL_WIDTH,
                (y + 1) * CELL_HEIGHT,
            };

            HBRUSH hbr;

            if ((x + y) % 2 == 0)
            {
                hbr = CreateSolidBrush(RGB(125, 250, 0));
            }
            else
            {
                hbr = CreateSolidBrush(RGB(175, 255, 45));
            }

            FillRect(hDC, &lprc, hbr);

            DeleteObject(hbr);
        }
    }
}

void DrawPlayer(HDC hDC)
{
    RECT lprc = {
        player.x * CELL_WIDTH,
        player.y * CELL_HEIGHT,
        (player.x + 1) * CELL_WIDTH,
        (player.y + 1) * CELL_HEIGHT,
    };

    HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 128));

    FillRect(hDC, &lprc, hbr);

    DeleteObject(hbr);
}

void DrawPlayerFood(HDC hDC)
{
    RECT lprc = {
        playerFood.x * CELL_WIDTH,
        playerFood.y * CELL_HEIGHT,
        (playerFood.x + 1) * CELL_WIDTH,
        (playerFood.y + 1) * CELL_HEIGHT,
    };

    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));

    FillRect(hDC, &lprc, hbr);

    DeleteObject(hbr);
}



void MovePlayer()
{
    if (player.x == playerFood.x && player.y == playerFood.y)
    {
        GeneratePlayerFood();
    }
}
