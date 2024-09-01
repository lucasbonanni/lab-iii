#ifndef MEMORY_H
#define MEMORY_H

void memory_init();       // Initializes the memory monitoring module (if necessary)
void memory_usage(long *total_mem, long *used_mem, long *free_mem); // Fetches memory statistics
void memory_cleanup();    // Cleans up resources (if necessary)

#endif
