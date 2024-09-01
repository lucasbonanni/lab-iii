#include <ncurses.h>
#include <unistd.h>

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
        mvprintw(1, 1, "CPU Usage: %d%%", 50);  // Dummy value for now
        refresh();
        usleep(500000);  // 0.5 seconds
    }

    cleanup_terminal();
    return 0;
}
