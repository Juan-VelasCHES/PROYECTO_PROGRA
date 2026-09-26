#include <iostream>
#include "supermario.h"
#include "colores.h"

using namespace std;

void set_console_color(int color_code) {
    cout<<colorANSI(color_code);
}

void crear_world(int background[ROWS][COLS]) {
    for(int i=0;i<ROWS;i++) {
        for(int j = 0; j<COLS;j++) {
            background[i][j] = WHITE;
        }
    }
}

void copy_matrix(const int source[ROWS][COLS], int destination[ROWS][COLS]) {

    for(int i=0;i<ROWS;i++) {
        for(int j = 0; j<COLS;j++) {
            destination[i][j] = source[i][j];
        }
    }
}

void draw_world(int world[ROWS][COLS]) {
    for(int i=0;i<ROWS;i++) {
        for(int j = 0; j<COLS;j++) {
            set_console_color(world[i][j]);
            cout<<"  ";
        }
    cout<<"\n";
    }
    cout << "\033[0m" << endl;
}

void place_floor(int background[ROWS][COLS]) {
    for(int i=44;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            background[i][j] = RED;
        }
    }
}


