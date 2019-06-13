#ifndef _INC_WCONSOLE    //don't let this file be included
#define _INC_WCONSOLE    //twice in the same source file

#include <stdlib.h>
#include <ncurses.h>
#include <zconf.h>

enum cCOLOR {
    cBLACK = COLOR_BLACK, cBLUE = COLOR_BLUE, cGREEN = COLOR_GREEN, cCYAN = COLOR_CYAN,
    cRED = COLOR_RED, cMAGENTA = COLOR_MAGENTA, cYELLOW = COLOR_YELLOW, cWHITE = COLOR_WHITE
};

void set_color(cCOLOR fg, cCOLOR bg = cBLACK);

typedef unsigned short WORD;

// x - position, y - row
void set_cursor_pos(int x, int y);

void get_cursor_pos(int &x, int &y);

void clear_screen(void);

void rectangle(int left, int top, int right, int bottom);

void bar(int left, int top, int right, int bottom);

void wait(int milliseconds);

void clear_line(int row);

int click_cursor(int &x, int &y);                          //*

WINDOW *hConsole;         //console handle
//--------------------------------------------------------------
void set_color(cCOLOR foreground, cCOLOR background) {
    init_pair(1, foreground, background);
    attron(COLOR_PAIR(1));
    refresh();
}

//--------------------------------------------------------------
void get_cursor_pos(int &x, int &y) {
    getyx(hConsole, y, x);
}

//--------------------------------------------------------------
void set_cursor_pos(int x, int y) {
    move(y, x);
    refresh();
}

//--------------------------------------------------------------
void rectangle(int left, int top, int right, int bottom) {
    int tmp, row, col;

    if (left > right) {
        tmp = left;
        left = right;
        right = tmp;
    }
    if (top > bottom) {
        tmp = top;
        top = bottom;
        bottom = tmp;
    }

    set_cursor_pos(left, top);
    addch(ACS_ULCORNER);
    set_cursor_pos(right, top);
    addch(ACS_URCORNER);
    set_cursor_pos(right, bottom);
    addch(ACS_LRCORNER);
    set_cursor_pos(left, bottom);
    addch(ACS_LLCORNER);

    col = left + 1;
    set_cursor_pos(col, top);
    for (; col < right; col++)
        addch(ACS_HLINE);

    col = left + 1;
    set_cursor_pos(col, bottom);
    for (; col < right; col++)
        addch(ACS_HLINE);

    row = top + 1;
    for (; row < bottom; row++) {
        set_cursor_pos(left, row);
        addch(ACS_VLINE);
    }

    row = top + 1;
    for (; row < bottom; row++) {
        set_cursor_pos(right, row);
        addch(ACS_VLINE);
    }
}

//--------------------------------------------------------------
void bar(int left, int top, int right, int bottom) {
    int tmp, row, i;
    char s[100];
    if (left > right) {
        tmp = left;
        left = right;
        right = tmp;
    }
    if (top > bottom) {
        tmp = top;
        top = bottom;
        bottom = tmp;
    }

    for (i = 0; i <= (right - left); i++)
        s[i] = ' ';
    s[i] = '\0';
    for (row = top; row <= bottom; row++) {
        set_cursor_pos(left, row);
        printw(s);
    }
}

//--------------------------------------------------------------
void clear_screen(void) {
    set_cursor_pos(0, 0);
    int height = getmaxy(hConsole);
    for (int j = 0; j <= height; j++)
        clear_line(j);
    set_cursor_pos(0, 0);
}

//--------------------------------------------------------------
void wait(int milliseconds) {
    refresh();
    usleep(static_cast<useconds_t>(milliseconds * 1000));
}

//--------------------------------------------------------------
void clear_line(int row) {
    set_cursor_pos(0, row);
    int width = getmaxx(hConsole);
    for (int j = 0; j <= width; j++) puts(" ");
}

//--------------------------------------------------------------
int click_cursor(int &x, int &y) {
    int i, width, height;
    noecho();
    width = getmaxx(hConsole);
    height = getmaxy(hConsole);
    get_cursor_pos(x, y);
    while (1) {
        set_cursor_pos(x, y);
        i = getch();
        if (i == 224 || i == 0)
            i = 1000 + getchar();
        switch (i) {
            case 27:   //Esc
                return 0;
            case 10:   //Enter
                return 1;
            case KEY_DOWN:   //Down
            case 's':
            case 'S':
                if (y < height)
                    y++;
                break;
            case KEY_UP:   //Up
            case 'w':
            case 'W':
                if (y > 0)
                    y--;
                break;
            case KEY_LEFT:   //<--
            case 'a':
            case 'A':
                if (x > 0)
                    x--;
                break;
            case KEY_RIGHT:   //-->
            case 'd':
            case 'D':
                if (x < width)
                    x++;
        }
    }
}
//--------------------------------------------------------------
#endif /* _INC_WCONSOLE */