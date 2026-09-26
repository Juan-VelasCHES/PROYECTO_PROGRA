#include "colores.h"

std::string colorANSI(int color)
{
    switch (color)
    {
        case 0: return "\033[47m";   // Blanco
        case 1: return "\033[101m";  // Rojo claro
        case 2: return "\033[40m";   // Negro
        case 3: return "\033[107m";  // Blanco brillante
        case 4: return "\033[104m";  // Azul
        case 5: return "\033[103m";  // Amarillo claro
        case 6: return "\033[41m";   // Rojo
        case 7: return "\033[42m";   // Verde
        case 8: return "\033[43m";   // Amarillo

        default: return "\033[47m";  // Blanco
    }
}