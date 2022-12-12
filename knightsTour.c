// link libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// macros
#define BOARD_SIZE 8
#define MARK_VISITED(BF, N) BF |= ((uint64_t) 0b1 << N)
#define UNMARK_VISITED(BF, N) BF &= ((uint64_t) 0b0 << N)
#define WAS_NOT_VISITED(BF, N) !((BF >> N) & 0b1)

// function prototypes
bool canMove(uint8_t direction, uint8_t row, uint8_t col);
void move(uint8_t moveNum, uint8_t movesToGo, uint8_t direction, uint8_t row, uint8_t col);
void changeRowCol(uint8_t direction, uint8_t *row, uint8_t *col);

// global variables
uint8_t board[BOARD_SIZE][BOARD_SIZE] = { 0 };
uint64_t visited = 0;

int main(void)
{
    uint8_t moveNum = 0, movesToGo = BOARD_SIZE * BOARD_SIZE;
    move(moveNum, movesToGo, 0, 0, 0);



    return 0;
}

bool canMove(uint8_t direction, uint8_t row, uint8_t col)
{
    switch(direction)
    {
    case 0: // Up-Left
        return row - 2 >= 0 && col - 1 >= 0 && WAS_NOT_VISITED(visited, ((row - 2) * BOARD_SIZE) + col - 1);
        break;
    case 1: // Up-Right
        return row - 2 >= 0 && col + 1 < BOARD_SIZE && WAS_NOT_VISITED(visited, ((row - 2) * BOARD_SIZE) + col + 1);
        break;
    case 2: // Right-Up
        return col + 2 < BOARD_SIZE && row - 1 >= 0 && WAS_NOT_VISITED(visited, ((col + 2) * BOARD_SIZE) + row - 1);
        break;
    case 3: // Right-Down
        return col + 2 < BOARD_SIZE && row + 1 < BOARD_SIZE && WAS_NOT_VISITED(visited, ((col + 2) * BOARD_SIZE) + row + 1);
        break;
    case 4: // Down-Right
        return row + 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && WAS_NOT_VISITED(visited, ((row + 2) * BOARD_SIZE) + col + 1);
        break;
    case 5: // Down-Left
        return row + 2 < BOARD_SIZE && col - 1 >= 0 && WAS_NOT_VISITED(visited, ((row + 2) * BOARD_SIZE) + col - 1);
        break;
    case 6: // Left-Down
        return col - 2 >= 0 && row + 1 < BOARD_SIZE && WAS_NOT_VISITED(visited, ((col - 2) * BOARD_SIZE) + row + 1);
        break;
    case 7: // Left-Up
        return col - 2 >= 0 && row - 1 >= 0 && WAS_NOT_VISITED(visited, ((col - 2) * BOARD_SIZE) + row - 1);
        break;
    default: // not a valid direction
        printf("%d is not a valid direction.\n", direction);
        break;
    }
}

void move(uint8_t moveNum, uint8_t movesToGo, uint8_t direction, uint8_t row, uint8_t col)
{
    uint8_t rotation = 0;
    MARK_VISITED(visited, row * BOARD_SIZE + col);
    *(*(board + row) + col) = moveNum++;
    puts("");
    printf("move#: %d\n", moveNum);
    printf("toGo: %d\n", movesToGo);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
            printf("%02d ", *(*(board + i) + j));
        puts("");
    }
    if(movesToGo-- == 0)
        return;
    while((direction + rotation) < 8 && !canMove(direction + rotation, row, col))
        rotation++;
    if((direction + rotation) < 8)
    {
        changeRowCol(direction + rotation, &row, &col);
        move(moveNum, movesToGo, 0, row, col);
    }
    else
    {
        UNMARK_VISITED(visited, row * BOARD_SIZE + col);
        changeRowCol((direction + 4) % 8, &row, &col);
        move(--moveNum, ++movesToGo, direction + rotation, row, col);
    }

}

void changeRowCol(uint8_t direction, uint8_t *row, uint8_t *col)
{
    switch (direction)
    {
    case 0: // Up-Left
        *row -= 2, --*col;
        break;
    case 1: // Up-Right
        *row -= 2, ++*col;
        break;
    case 2: // Right-Up
        *col += 2, --*row;
        break;
    case 3: // Right-Down
        *col += 2, ++*row;
        break;
    case 4: // Down-Right
        *row += 2, ++*col;
        break;
    case 5: // Down-Left
        *row += 2, --*col;
        break;
    case 6: // Left-Down
        *col -= 2, ++*row;
        break;
    case 7: // Left-Up
        *col -= 2, --*row;
        break;
    default: // not a valid direction
        printf("%d is not a valid direction.\n", direction);
    }
}
