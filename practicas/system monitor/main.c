#include <ncurses.h>
#include <unistd.h>
#include "cpu.h"

void setup_terminal() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
}

void cleanup_terminal() {
    endwin();
}

int main() {
    setup_terminal();

    while (1) {
        clear();
        float usage = cpu_usage();
        mvprintw(1, 1, "CPU Usage: %.2f%%", usage);  // Dummy value for now
        refresh();
        usleep(500000);  // 0.5 seconds
    }

    cleanup_terminal();
    return 0;
}
