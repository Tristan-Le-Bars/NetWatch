#include <iostream>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "../headers/machine_ressources.h"


MachineRessources::MachineRessources(){
    // Open /proc/stat
    setProcStat();

    // Read the first line (cpu stats)
    fscanf(proc_stat, "cpu %llu %llu %llu %llu %llu %llu %llu",
            &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(proc_stat);

    // Calculate total and idle time
    total1 = user + nice + system + idle + iowait + irq + softirq;
    total_idle = idle + iowait;
}

MachineRessources::~MachineRessources(){

}


void MachineRessources::updateRessourcesInfo(){
    setSysinfo();
    setStatvfs();
    setProcStat();
}


int MachineRessources::setSysinfo(){
    if (sysinfo(&info) != 0) {
        perror("sysinfo failed");
        return -1;
    }
    return 0;
}

int MachineRessources::setStatvfs(){
    if (statvfs("/", &stat) != 0) {
        perror("statvfs failed");
        return -1;
    }
    return 0;
}

int MachineRessources::setProcStat(){
    proc_stat = fopen("/proc/stat", "r");
    if (proc_stat == NULL) {
        perror("Failed to open /proc/stat");
        return 1;
    }
    return 0;
}

std::string MachineRessources::getUpTime(){
    
}

void MachineRessources::getStorageUsage(){
    total_space = stat.f_blocks * stat.f_frsize; // Total size in bytes
    free_space = stat.f_bfree * stat.f_frsize;   // Free space in bytes
    available_space = stat.f_bavail * stat.f_frsize; // Available space in bytes
}

void MachineRessources::getRAMUsage(){
    // Calculate and display RAM data in megabytes
    total_ram_mb = info.totalram / (1024 * 1024); // Convert bytes to MB
    free_ram_mb = info.freeram / (1024 * 1024);   // Convert bytes to MB
    buffer_ram_mb = info.bufferram / (1024 * 1024); // Convert bytes to MB
    cached_ram_mb = info.cachedram / (1024 * 1024); // Convert bytes to MB
}

void MachineRessources::getCPUUsage(){
    // Read the stats again
    setProcStat();
    fscanf(proc_stat, "cpu %llu %llu %llu %llu %llu %llu %llu",
            &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(proc_stat);

    // Calculate total and idle time again
    total2 = user + nice + system + idle + iowait + irq + softirq;
    total_idle += (idle + iowait);

    // Calculate CPU usage
    cpu_usage = 100 * (1 - (double)(total_idle - (idle + iowait)) / (total2 - total1));

    // Print CPU usage
    printf("CPU Usage: %llu%%\n", cpu_usage);
    total1 = total2
}