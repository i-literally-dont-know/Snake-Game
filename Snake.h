#ifndef SNAKE_H
#define SNAKE_H

#define MAX_LENGTH 100

typedef struct _Point_
{
    int x;
    int y;

} Point;

typedef struct _Snake_
{

    int length;
    int dx; // movement in x
    int dy; // movement in y
    Point body[MAX_LENGTH];

} Snake;

typedef struct _Food_
{
    int x;
    int y;

} Food;

void initSnake(Snake *s);
void moveSnake(Snake *s);
void changeDirection(Snake *s, int dx, int dy);
// int eatFood(Snake *s);
int hitWall(Snake *s, int x_end, int y_end);
int snakePos(Snake *s, int x, int y);
int hitSelf(Snake *s);
void printSnake(Snake *s);
int snakePos(Snake *s, int x, int y);
void spawnFood(Food *f, Snake *s);

#endif