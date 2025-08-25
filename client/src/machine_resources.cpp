#include <iostream>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "../include/machine_resources.h"



MachineResources::MachineResources(std::string id)
: client_id(id), user(0), nice(0), system(0), idle(0), iowait(0), irq(0), softirq(0),
total1(0), total2(0), total_idle(0), cpu_usage(0.0) {
    client_id = id;
    setProcStat();
    fscanf(proc_stat, "cpu %llu %llu %llu %llu %llu %llu %llu",
            &user, &nice, &system, &idle, &iowait, &irq, &softirq);
    fclose(proc_stat);

    // Calculate total and idle time
    total1 = user + nice + system + idle + iowait + irq + softirq;
    total_idle = idle + iowait;
}

MachineResources::~MachineResources(){

}


void MachineResources::updateResourcesInfo(){
    std::lock_guard<std::mutex> lock(resourceMutex);
    setSysinfo();
    setStatvfs();
}


int MachineResources::setSysinfo(){
    if (sysinfo(&info) != 0) {
        perror("sysinfo failed");
        return -1;
    }
    return 0;
}

int MachineResources::setStatvfs(){
    if (statvfs("/", &stat) != 0) {
        perror("statvfs failed");
        return -1;
    }
    return 0;
}

int MachineResources::setProcStat(){
    proc_stat = fopen("/proc/stat", "r");
    if (proc_stat == NULL) {
        perror("Failed to open /proc/stat");
        return 1;
    }
    return 0;
}

std::string MachineResources::getUpTime(){
    std::lock_guard<std::mutex> lock(resourceMutex);
    return "getUpTime not implemented";
}

void MachineResources::getStorageUsage(){
    std::lock_guard<std::mutex> lock(resourceMutex);
    total_space = (stat.f_blocks * stat.f_frsize) / (1024.0 * 1024 * 1024); // Total size in bytes
    free_space = (stat.f_bfree * stat.f_frsize) / (1024.0 * 1024 * 1024);   // Free space in bytes
    available_space = (stat.f_bavail * stat.f_frsize) / (1024.0 * 1024 * 1024); // Available space in bytes
}

void MachineResources::getRAMUsage(){
    std::lock_guard<std::mutex> lock(resourceMutex);
    total_ram_mb = info.totalram / (1024.0 * 1024.0 * 1024.0); // Convert bytes to MB
    free_ram_mb = info.freeram / (1024.0 * 1024.0 * 1024.0);   // Convert bytes to MB
    buffer_ram_mb = info.bufferram / (1024.0 * 1024.0 * 1024.0); // Convert bytes to MB
}

void MachineResources::getCPUUsage() {
    std::lock_guard<std::mutex> lock(resourceMutex);
    setProcStat();
    if (proc_stat) {
        if (fscanf(proc_stat, "cpu %llu %llu %llu %llu %llu %llu %llu",
                   &user, &nice, &system, &idle, &iowait, &irq, &softirq) == 7) {
            fclose(proc_stat);

            // Calculate total and idle time again
            total2 = user + nice + system + idle + iowait + irq + softirq;
            unsigned long long idle2 = idle + iowait;

            // Calculate CPU usage
            if (total2 != total1) {
                cpu_usage = 100.0 * (1.0 - (double)(idle2 - total_idle) / (total2 - total1));
            } else {
                cpu_usage = 0.0;
            }


            total1 = total2;
            total_idle = idle2;
        } else {
            std::cerr << "Failed to read CPU stats from /proc/stat" << std::endl;
            fclose(proc_stat);
        }
    }
}

std::string MachineResources::getFormattedData(){
    std::lock_guard<std::mutex> lock(resourceMutex);
    
    std::string datatype = "resources_data";
    std::string formated_data;
    std::string total_ram_str = std::to_string(total_ram_mb);
    std::string free_ram_str = std::to_string(free_ram_mb);
    std::string buffer_ram_str = std::to_string(buffer_ram_mb);

    std::string total_space_str = std::to_string(total_space);
    std::string free_space_str = std::to_string(free_space);
    std::string available_space_str = std::to_string(available_space);
    std::string cpu_usage_str = std::to_string(cpu_usage);

  
    formated_data = "{\n   \"datatype\": \"" + datatype + "\",\n" +
                    "   \"client_id\": \"" + client_id + "\",\n"
                    "   \"resources\": {\n" +
                    "       \"total_ram\": " + total_ram_str + ",\n" +
                    "       \"free_ram\": " + free_ram_str + ",\n" +
                    "       \"buffer_ram\": " + buffer_ram_str + ",\n" +
                    "       \"total_space\": " + total_space_str + ",\n" +
                    "       \"free_space\": " + free_space_str + ",\n" +
                    "       \"available_space\": " + available_space_str + ",\n" +
                    "       \"cpu_usage\": " + cpu_usage_str + ",\n" +
                    "   }\n"
                    "}";
    return formated_data;
}

