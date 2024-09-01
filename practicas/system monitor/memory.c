#include "memory.h"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <stdio.h>

void memory_init() {
    // Initialize resources if necessary
}

void memory_usage(long *total_mem, long *used_mem, long *free_mem) {
    // Fetch memory statistics
    // Get total memory
    int64_t total_memory = 0;
    size_t length = sizeof(total_memory);
    if (sysctlbyname("hw.memsize", &total_memory, &length, NULL, 0) != 0) {
        perror("Error al obtener la memoria total");
        return;
    }
    mach_port_t host_port = mach_host_self();
    vm_size_t page_size;
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    vm_statistics64_data_t vm_stats;

    if (host_page_size(host_port, &page_size) != KERN_SUCCESS ||
        host_statistics64(host_port, HOST_VM_INFO, (host_info64_t)&vm_stats, &count) != KERN_SUCCESS) {
        perror("Failed to fetch vm statistics");
        return;
    }

   // Calculate memory statistics
    *total_mem = total_memory;
    long free_memory = (vm_stats.free_count + vm_stats.inactive_count) * page_size;
    long active_memory = vm_stats.active_count * page_size;
    long wired_memory = vm_stats.wire_count * page_size;
    *used_mem = active_memory + wired_memory;
    *free_mem = free_memory;
}

void memory_cleanup() {
    // Clean up resources if necessary
}