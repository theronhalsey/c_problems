// link libraries
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// macros
#define BOARD_SIZE 7

// function prototypes
void move();
void changeRowCol();
bool canMove();
uint_fast8_t undoMove();

// global variables
uint_fast8_t board[BOARD_SIZE][BOARD_SIZE] = {0};
uint_fast8_t moveNum = 1, row = 0, col = 0, direction = 0;
uint_fast64_t totalMoves = 1;

int main(void)
{
    clock_t start, end;
    double solveTime;

    for (uint_fast8_t i = 0; i < BOARD_SIZE; i++)
    {
        for(uint_fast8_t j = 0; j < BOARD_SIZE; j++)
        {
            memset(board, 0, sizeof(board));
            moveNum = 1, row = i, col = j, direction = 0;
            totalMoves = 1;
            start = clock();
            while(moveNum != 0 && moveNum != BOARD_SIZE * BOARD_SIZE)
                move(direction);
            *(*(board + row) + col) = moveNum;
            end = clock();
            solveTime = ((double)(end-start)) / CLOCKS_PER_SEC;
            for (uint_fast8_t k = 0; k < BOARD_SIZE; k++)
            {
                for (uint_fast8_t l = 0; l < BOARD_SIZE; l++)
                    printf("%02d ", *(*(board + k) + l));
                puts("");
            }
            printf("total moves: %lld\ntime: %llf\n\n", totalMoves, solveTime);
        }
        puts("");
    }

    return 0;
}

void move()
{
    totalMoves++;
    while((direction) < 8 && !canMove(direction))
        direction++;
    if((direction) < 8)
    {
        *(*(board + row) + col) = moveNum;
        changeRowCol(direction);
        direction = 0;
        moveNum++;
    }
    else
    {
        *(*(board + row) + col) = 0;
        --moveNum;
        direction = (undoMove() + 4) % 8 + 1;
    }
}

void changeRowCol()
{
    switch (direction)
    {
    case 0: // Up-Left
        row -= 2, --col;
        break;
    case 1: // Up-Right
        row -= 2, ++col;
        break;
    case 2: // Right-Up
        col += 2, --row;
        break;
    case 3: // Right-Down
        col += 2, ++row;
        break;
    case 4: // Down-Right
        row += 2, ++col;
        break;
    case 5: // Down-Left
        row += 2, --col;
        break;
    case 6: // Left-Down
        col -= 2, ++row;
        break;
    case 7: // Left-Up
        col -= 2, --row;
        break;
    }
}

bool canMove()
{

    switch(direction)
    {
    case 0: // Up-Left
        return row - 2 >= 0 && col - 1 >= 0 && *(*(board + row - 2) + col - 1) == 0;
        break;
    case 1: // Up-Right
        return row - 2 >= 0 && col + 1 < BOARD_SIZE && *(*(board + row - 2) + col + 1) == 0;
        break;
    case 2: // Right-Up
        return col + 2 < BOARD_SIZE && row - 1 >= 0 && *(*(board + row - 1) + col + 2) == 0;
        break;
    case 3: // Right-Down
        return col + 2 < BOARD_SIZE && row + 1 < BOARD_SIZE && *(*(board + row + 1) + col + 2) == 0;
        break;
    case 4: // Down-Right
        return row + 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && *(*(board + row + 2) + col + 1) == 0;
        break;
    case 5: // Down-Left
        return row + 2 < BOARD_SIZE && col - 1 >= 0 && *(*(board + row + 2) + col - 1) == 0;
        break;
    case 6: // Left-Down
        return col - 2 >= 0 && row + 1 < BOARD_SIZE && *(*(board + row + 1) + col - 2) == 0;
        break;
    case 7: // Left-Up
        return col - 2 >= 0 && row - 1 >= 0 && *(*(board + row - 1) + col - 2) == 0;
        break;
    }
}

uint_fast8_t undoMove()
{
    // Up-Left
    if (row - 2 >= 0 && col - 1 >= 0 && *(*(board + row - 2) + col - 1) == moveNum)
    {
        row -= 2, --col;
        return 0;
    }
    // Up-Right
    if (row - 2 >= 0 && col + 1 < BOARD_SIZE && *(*(board + row - 2) + col + 1) == moveNum)
    {
        row -= 2, ++col;
        return 1;
    }
    // Right-Up
    if (col + 2 < BOARD_SIZE && row - 1 >= 0 && *(*(board + row - 1) + col + 2) == moveNum)
    {
        col += 2, --row;
        return 2;
    }
    // Right-Down
    if (col + 2 < BOARD_SIZE && row + 1 < BOARD_SIZE && *(*(board + row + 1) + col + 2) == moveNum)
    {
        col += 2, ++row;
        return 3;
    }
    // Down-Right
    if (row + 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && *(*(board + row + 2) + col + 1) == moveNum)
    {
        row += 2, ++col;
        return 4;
    }
    // Down-Left
    if (row + 2 < BOARD_SIZE && col - 1 >= 0 && *(*(board + row + 2) + col - 1) == moveNum)
    {
        row += 2, --col;
        return 5;
    }
    // Left-Down
    if (col - 2 >= 0 && row + 1 < BOARD_SIZE && *(*(board + row + 1) + col - 2) == moveNum)
    {
        col -= 2, ++row;
        return 6;
    }
    // Left-Up
    if (col - 2 >= 0 && row - 1 >= 0 && *(*(board + row - 1) + col - 2) == moveNum)
    {
        col -= 2, --row;
        return 7;
    }
}
