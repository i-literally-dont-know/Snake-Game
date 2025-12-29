#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#include "Snake.h"

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 10

// forward declarations
void printWelcomeMessage(void);
int startGameLoop(Snake *s);
int getInput(Snake *s);
void printBoard(Food *f, Snake *s);
int eatFood(Snake *s, Food *f);

int main(void)
{
    initscr();       // start ncurses
    noecho();        // don’t echo keys
    curs_set(FALSE); // hide cursor
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    printWelcomeMessage();
    int round = 0;
    Snake s;
    initSnake(&s);
    startGameLoop(&s);

    endwin();
    return 0;
}

void printWelcomeMessage(void)
{
    nodelay(stdscr, FALSE);
    clear();
    mvprintw(1, 2, "=============================");
    mvprintw(2, 2, "= Welcome to the snake game =");
    mvprintw(3, 2, "=============================");
    mvprintw(5, 2, "Press any key to start...");
    refresh();
    getch();
    nodelay(stdscr, TRUE);
}

int startGameLoop(Snake *s)
{
    Food f;
    bool spawn = true;
    while (1)
    {
        getInput(s);
        moveSnake(s);
        if (spawn == true)
        {
            spawnFood(&f, s);
        }

        if (hitWall(s, BOARD_WIDTH, BOARD_HEIGHT) || hitSelf(s))
        {
            clear();
            mvprintw(BOARD_HEIGHT / 2, BOARD_WIDTH / 2 - 5, "Game Over");
            refresh();
            nodelay(stdscr, FALSE);
            getch();
            break;
        }
        if (eatFood(s, &f) == 0)
        {
            spawn = true;
        }
        else
        {
            spawn = false;
        }

        printBoard(&f, s);
        usleep(600000);
    }
    return 0;
}

int getInput(Snake *s)
{

    int c = getch();
    switch (c)
    {
    case KEY_UP:
        changeDirection(s, 0, -1);
        break;
    case KEY_DOWN:
        changeDirection(s, 0, 1);
        break;
    case KEY_LEFT:
        changeDirection(s, -1, 0);
        break;
    case KEY_RIGHT:
        changeDirection(s, 1, 0);
        break;
    default:
        break;
    }
    return 0;
}

void printBoard(Food *f, Snake *s)
{
    clear();

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (x == 0 || y == 0 ||
                x == BOARD_WIDTH - 1 ||
                y == BOARD_HEIGHT - 1)
            {
                mvaddch(y, x, '#');
                continue;
            }

            int idx = snakePos(s, x, y);
            if (x == f->x && y == f->y)
            {
                mvaddch(y, x, '*');
                continue;
            }
            if (idx == 0)
                mvaddch(y, x, 'O');
            else if (idx > 0)
                mvaddch(y, x, 'o');
            else
                mvaddch(y, x, ' ');
        }
    }

    refresh();
}

void spawnFood(Food *f, Snake *s)
{
    do
    {
        f->x = rand() % (BOARD_WIDTH - 2) + 1;
        f->y = rand() % (BOARD_HEIGHT - 2) + 1;
    } while (snakePos(s, f->x, f->y) != -1);
}

int eatFood(Snake *s, Food *f)
{
    if (s->body[0].x == f->x && s->body[0].y == f->y)
    {
        return 0;
    }
    return -1;
}
