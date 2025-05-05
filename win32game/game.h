#ifndef GAME_H
#define GAME_H

#include "header.h"

#define CELL_WIDTH      25
#define CELL_HEIGHT     25
#define COLS_COUNT      21
#define ROWS_COUNT      21
#define CANVAS_WIDTH    CELL_WIDTH * COLS_COUNT
#define CANVAS_HEIGHT   CELL_HEIGHT * ROWS_COUNT

POINT player;
POINT playerFood;

void InitGame(HWND hWnd);

void HandleInput(HWND hWnd, WPARAM wParam);

void GeneratePlayer();
void GeneratePlayerFood();

void DrawField(HDC hDC);
void DrawPlayer(HDC hDC);
void DrawPlayerFood(HDC hDC);

BOOL MovePlayer();

#endif // !GAME_H
