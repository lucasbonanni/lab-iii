#include "cpu.h"
#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <stdio.h>

static host_cpu_load_info_data_t previous_cpu_info;

void cpu_init() {
    // Initialization code for CPU monitoring
    // Initialize with zeroes
    memset(&previous_cpu_info, 0, sizeof(previous_cpu_info));
}

float cpu_usage() {
    // Code to update CPU usage
    host_cpu_load_info_data_t cpu_info;
    // Get CPU info from the host
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    // Get CPU statistics from the host system call
    // Returns KERN_SUCCESS if successful or an error code otherwise
    // The host_statistics function is used to retrieve information about the host system
    // The HOST_CPU_LOAD_INFO parameter specifies that we want to retrieve CPU load information
    // The cpu_info structure will be filled with the CPU load information
    // The count variable specifies the number of elements in the cpu_info structure
    kern_return_t kr = host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpu_info, &count);

    if (kr != KERN_SUCCESS) {
        perror("Error al obtener estadísticas de CPU");
        return -1;
    }
    // Calculate CPU usage percentage
    uint64_t total_ticks = 0;
    uint64_t used_ticks = 0;

    // The CPU states are defined in the host_info.h header file
    // The CPU_STATE_MAX constant specifies the maximum number of CPU states
    // The CPU_STATE_IDLE constant specifies the CPU state for idle time
    for (int i = 0; i < CPU_STATE_MAX; i++) {
        // Calculate the difference between the current and previous CPU ticks
        uint64_t ticks = cpu_info.cpu_ticks[i] - previous_cpu_info.cpu_ticks[i];
        // Add the difference to the total and used ticks
        total_ticks += ticks;
        // Skip the idle state
        if (i != CPU_STATE_IDLE) {
            // Add the difference to the used ticks
            used_ticks += ticks;
        }
    }
    // Save current CPU info for next iteration
    previous_cpu_info = cpu_info;

    // Return CPU usage percentage
    if (total_ticks == 0) {
        return 0;
    }
    // Calculate the CPU usage percentage
    return (float)used_ticks / total_ticks * 100;
}

void cpu_cleanup() {
    // Code to clean up CPU monitoring resources
}
