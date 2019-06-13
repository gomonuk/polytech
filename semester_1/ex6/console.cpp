#include "console.h"
#include <stdlib.h>
#include <ncurses.h>


// 17
//Разработать визуальную компоненту VertProgressBar (вертикальный прогресс бар).
//
class VertProgressBar {
private:
    int Left;
    int top;
    float max_value;
    int number_step;
    const char *title;

public:
    VertProgressBar (int Left, int Top, float MaxValue, int NumberStep, const char *Title=NULL){
//        left = Left;
        top = Top;
        max_value = MaxValue;
        number_step = NumberStep;
        title = Title;

        initscr();
        hConsole = stdscr;
        keypad(hConsole, true);
        // поддержка цветов
        if (has_colors() == FALSE) {
            endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }

        start_color();
        set_color(cYELLOW, cBLUE);
    };

   ~VertProgressBar(){
       clear_screen();
       endwin();
   };


    void Start(void){

        int left   = 2 + this->Left;
        int right  = 8 + this->Left;
        int top    = 0 + this->top;
        int bottom = 2 + this->top;

        for (int i = 0; i < number_step; ++i) {
            bar(left, top, right, bottom);
            rectangle(left, top, right, bottom);
            bottom += 2;
            sleep(1);
        }

        set_cursor_pos(left+1, bottom/2);
        printw(title);
        refresh();

    }
    void Hide(void){
        set_color(cWHITE, cBLACK);
    };

    void Show(void){
        set_color(cYELLOW, cBLUE);
    };
};

int main(void) {
    VertProgressBar ob1(0, 2, 0.2, 3, " All!");
    ob1.Start();
    sleep(2);

    ob1.Hide();
    sleep(2);

    ob1.Show();
    sleep(2);
}
//gcc -o 6ex console.cpp -lncurses -lstdc++
