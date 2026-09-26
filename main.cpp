#include <iostream>
#include "supermario.h"

int main() {
    int background[ROWS][COLS];
    int world[ROWS][COLS];

    // 1. Inicializar el fondo en blanco
    crear_world(background);

    // 2. Colocar el suelo rojo en la parte inferior
    place_floor(background);

    // 3. Copiar el fondo a la matriz activa de renderizado
    copy_matrix(background, world);

    // 4. Dibujar el mundo en consola
    draw_world(world);

    std::cout << "\nPresiona Enter para salir...";
    std::cin.get();

    return 0;
}