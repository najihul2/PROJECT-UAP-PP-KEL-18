#include <curses.h>
#include <cstdlib>
#include <ctime>
#include "GameSystem.cpp"

int main() {
    // Inisialisasi Ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0); // Sembunyikan kursor
    keypad(stdscr, TRUE); // Aktifkan tombol panah
    
    // Seed Random
    srand(time(0));
    
    // Masuk ke Game System
    mainMenu();
    
    // Bersihkan Ncurses saat keluar
    endwin();
    return 0;
}
