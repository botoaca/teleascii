#include "include/Util.h"

void
CLEAR_SCREEN() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}