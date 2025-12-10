#include <curses.h>

void drawTitle(int y, int x) {
    attron(A_BOLD);
    mvprintw(y, x,   " ___ _                 ");
    mvprintw(y+1, x, "| __| | __ _ _ __ _  _   ");
    mvprintw(y+2, x, "| _|| |/ _` | '_ \\ '_ \\ || | ");
    mvprintw(y+3, x, "|_| |_|\\__,_| .__/ .__/\\_, | ");
    mvprintw(y+4, x, "            |_|  |_|   |__/  ");
    attroff(A_BOLD);
}

void drawGameOverText(int y, int x) {
    attron(A_BOLD);
    mvprintw(y, x,   "  ___   _   __  __ ___ ");
    mvprintw(y+1, x, " / __| /_\\ |  \\/  | __|");
    mvprintw(y+2, x, "| (_ |/ _ \\| |\\/| | _| ");
    mvprintw(y+3, x, " \\___/_/ \\_\\_|  |_|___|");
    mvprintw(y+4, x, "     _____   _____ ___ ");
    mvprintw(y+5, x, "    / _ \\ \\ / / __| _ \\");
    mvprintw(y+6, x, "   | (_) \\ V /| _||   /");
    mvprintw(y+7, x, "    \\___/ \\_/ |___|_|_\\");
    attroff(A_BOLD);
}
