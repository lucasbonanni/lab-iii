#include <ncurses.h>
#include <unistd.h>
#include "cpu.h"
#include "memory.h"

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
    long total_mem, used_mem, free_mem;
    while (1) {
        clear();
        float cpu_percent = cpu_usage();
        memory_usage(&total_mem, &used_mem, &free_mem);

         mvprintw(1, 1, "CPU Usage: %.2f%%", cpu_percent);
        mvprintw(2, 1, "Total Memory: %ld MB", total_mem / (1024 * 1024));
        mvprintw(3, 1, "Used Memory: %ld MB", used_mem / (1024 * 1024));
        mvprintw(4, 1, "Free Memory: %ld MB", free_mem / (1024 * 1024));
        refresh();
        usleep(500000);  // 0.5 seconds
    }

    cleanup_terminal();
    return 0;
}
