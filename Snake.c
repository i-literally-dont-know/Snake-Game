#include <stdio.h>
#include "Snake.h"
#include "Game.h"

void initSnake(Snake *s)
{
    s->length = 3;
    s->dx = 1;
    s->dy = 0;
    s->body[0] = (Point){5, 4};
    s->body[1] = (Point){4, 4};
    s->body[2] = (Point){3, 4};
}

void moveSnake(Snake *s)
{
    for (int i = s->length - 1; i > 0; i--)
    {
        s->body[i] = s->body[i - 1];
    }

    s->body[0].x += s->dx;
    s->body[0].y += s->dy;
}
/*
void eatFood(Snake *s)
{
    if (s->length >= MAX_LENGTH)
        return;
    s->body[s->length] = s->body[s->length - 1];
    s->length++;
}*/

void changeDirection(Snake *s, int dx, int dy)
{
    if (s->dx == -dx && s->dy == -dy)
    {
        return;
    }

    s->dx = dx;
    s->dy = dy;
}

void printSnake(Snake *s)
{
    for (int m = 0; m < s->length - 1; m++)
    {

        printf("o");
    }
    printf("O");
}

// is there any segment of the snake at x, y
// -1 = no, 0 = head, >0 = body
// while im printing the board i do this
int snakePos(Snake *s, int x, int y)
{
    for (int i = 0; i < s->length; i++)
    {
        if (s->body[i].x == x && s->body[i].y == y)
        {
            return i; // 0 = head, >0 = body
        }
    }
    return -1;
}

int hitWall(Snake *s, int x_end, int y_end)
{
    int x = s->body[0].x;
    int y = s->body[0].y;

    if (x <= 0 || x >= x_end - 1 ||
        y <= 0 || y >= y_end - 1)
    {
        return 1;
    }
    return 0;
}

int hitSelf(Snake *s)
{
    int head_x = s->body[0].x;
    int head_y = s->body[0].y;

    for (int i = 1; i < s->length; i++)
    {
        if (s->body[i].x == head_x &&
            s->body[i].y == head_y)
        {
            return 1;
        }
    }
    return 0;
}