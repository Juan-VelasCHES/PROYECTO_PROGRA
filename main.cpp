#include <iostream>
#include "supermario.h"

int main() {
    int background[ROWS][COLS];
    int world[ROWS][COLS];

    crear_world(background);

    place_floor(background);

    copy_matrix(background, world);

    draw_world(world);

    std::cout << "\nPresiona Enter para salir...";
    std::cin.get();

    return 0;
}
