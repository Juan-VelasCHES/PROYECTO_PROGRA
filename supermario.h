#ifndef SUPERMARIO_H
#define SUPERMARIO_H

#include <string>
using namespace std;

// =====================================================================
//  CONTRATO COMPARTIDO DEL EQUIPO (usa matrices normales, sin vector)
// =====================================================================

// ----------------- Tamaño del mundo -----------------
const int ROWS = 50;
const int COLS = 120;

// ----------------- Paleta de colores (Figura 2) -----------------
    enum Color {
        WHITE = 0,
        LIGHTRED_EX = 1,
        BLACK = 2,
        LIGHTWHITE_EX = 3,
        LIGHTBLUE_EX = 4,
        LIGHTYELLOW_EX = 5,
        RED = 6,
        GREEN = 7,
        YELLOW = 8
    };

// ----------------- Coordenadas fijas (definir en equipo) -----------------
const int MARIO_START_ROW = 34;
const int MARIO_START_COL = 8;

const int GOOMBA_ROW = 34;
const int GOOMBA_COL = 100;

const int SIGN_BLOCK_ROWS[3] = {15, 15, 15};
const int SIGN_BLOCK_COLS[3] = {30, 75, 95};

const int WOOD_BLOCK_ROWS[3] = {15, 15, 15};
const int WOOD_BLOCK_COLS[3] = {70, 90, 100};

const int TREE_ROWS[3] = {40, 40, 40};
const int TREE_COLS[3] = {12, 60, 96};

// ----------------- Tamaños de sprites -----------------
const int MARIO_H = 16, MARIO_W = 12;
const int GOOMBA_H = 16, GOOMBA_W = 16;
const int BLOCK_H = 9, BLOCK_W = 9;   // madera y signo
const int GRASS_H = 7, GRASS_W = 8;   // arbolitos

// ----------------- Movimiento -----------------
const int MOVE_H = 12; // right / left
const int MOVE_V = 16; // up (salto)

// =====================================================================
//  MODULO 1 (Persona A): Motor de color y mundo base
// =====================================================================
void set_console_color(int color_code);
// No retorna nada. Solo imprime el código ANSI de ese color para que
// lo que se imprima después salga pintado de ese color.

void crear_world(int background[ROWS][COLS]);
// No retorna nada. Llena TODA la matriz con WHITE. Esta matriz se
// convertirá en el "escenario fijo" (background): piso, árboles,
// bloques y goomba se estampan aquí UNA SOLA VEZ, al hacer "init",
// y nunca se vuelven a tocar (salvo place_used_block).

void copy_matrix(const int source[ROWS][COLS], int destination[ROWS][COLS]);
// No retorna nada. Copia, celda por celda, todo el contenido de
// "source" hacia "destination". Se usa UNA VEZ al iniciar el juego,
// para que "world" (la matriz que se muestra en pantalla) empiece
// siendo una copia exacta de "background" (el escenario fijo).

void draw_world(int world[ROWS][COLS]);
// No retorna nada. Recorre la matriz fila por fila, columna por columna,
// y usa set_console_color() para imprimir cada celda en pantalla.

void place_floor(int background[ROWS][COLS]);
// No retorna nada. Pinta la última fila (o las últimas filas) de la
// matriz con el patrón de piso de ladrillo. Se aplica sobre
// "background" (el escenario fijo), no sobre "world".

// =====================================================================
//  MODULO 2 (Persona B): Elementos estáticos (sprites fijos)
// =====================================================================
void place_tree(int background[ROWS][COLS], int row, int col);
void place_wood_block(int background[ROWS][COLS], int row, int col);
void place_sign_block(int background[ROWS][COLS], int row, int col);
void place_goomba(int background[ROWS][COLS], int row, int col);
// Ninguna retorna nada. Cada una recibe la matriz "background" (el
// escenario fijo) y la esquina superior-izquierda (row, col) donde
// debe "estampar" su sprite. Se llaman UNA SOLA VEZ, al hacer "init".

void place_used_block(int m[ROWS][COLS], int row, int col);
// No retorna nada. Vuelve a estampar ese mismo bloque pero en BLACK,
// tapando el "?". Cuando se recolecta una moneda, se llama DOS veces:
// una pasándole "background" (para que quede negro para siempre) y
// otra pasándole "world" (para que se vea negro de inmediato en
// pantalla, sin esperar al próximo redibujado completo).

// =====================================================================
//  MODULO 3 (Persona C): Mario (dibujo y movimiento)
// =====================================================================
void draw_player(int world[ROWS][COLS], int row, int col);
// No retorna nada. Estampa el sprite de Mario en (row, col), sobre
// la matriz "world" (la que se muestra en pantalla).

void erase_player(int world[ROWS][COLS], const int background[ROWS][COLS], int row, int col);
// No retorna nada. Restaura esa zona de "world" copiando lo que dice
// "background" en esas mismas celdas — así, si ahí había un árbol,
// piso, o cualquier otra cosa, reaparece tal cual estaba. Ya NO pinta
// blanco a ciegas, para no "comerse" lo que había debajo de Mario.

bool move_player(int world[ROWS][COLS], int &row, int &col, string option);
// Recibe la posición ACTUAL de Mario por referencia (&row, &col), o
// sea que esta función puede modificarla directamente.
// - Si el movimiento es válido: actualiza row y col a la nueva
//   posición y RETORNA true.
// - Si el movimiento saca a Mario del mundo: imprime "invalid
//   operation", NO modifica row/col, y RETORNA false.
// Quien la use (Persona D) debe revisar el true/false antes de seguir,
// por ejemplo para no intentar recolectar monedas si el paso fue inválido.

// =====================================================================
//  MODULO 4 (Persona D): Lógica de juego y main.cpp
// =====================================================================
bool collect_coings(int player_row, int player_col, bool collected[3], int &coins);
// Compara (player_row, player_col) contra las 3 posiciones de
// SIGN_BLOCK_ROWS/COLS. Si Mario está justo debajo/tocando un bloque
// signo que todavía no fue recolectado (collected[i] == false):
//   - marca collected[i] = true
//   - suma 1 a coins (parámetro por referencia)
//   - RETORNA true
// Si no hay ninguna recolección nueva, RETORNA false y no cambia nada.
// coins se recibe por referencia porque main.cpp necesita ver el
// contador actualizado después de llamar a esta función.
// IMPORTANTE: la comparación NO es "misma casilla exacta", es
// "el rectángulo de Mario (MARIO_H x MARIO_W) se solapa con el
// rectángulo del bloque (BLOCK_H x BLOCK_W)", porque tienen tamaños
// distintos.

bool check_game_over(int player_row, int player_col);
// Compara la posición de Mario con GOOMBA_ROW / GOOMBA_COL.
// RETORNA true si coinciden (Mario tocó al goomba -> game over).
// RETORNA false si no hay colisión.
// main.cpp usa este true/false para decidir si imprime "game over"
// y termina el programa.
// IMPORTANTE: igual que en collect_coings, se compara el rectángulo
// de Mario (MARIO_H x MARIO_W) contra el del goomba (GOOMBA_H x
// GOOMBA_W), no una casilla exacta.

#endif
