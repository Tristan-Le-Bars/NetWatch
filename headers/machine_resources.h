
#ifndef CLASS_MACHINE_RESOURCES
#define CLASS_MACHINE_RESOURCES

#include <iostream>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <vector>
#include <string>

class MachineResources {

    public:
        MachineResources();
        ~MachineResources();

        std::string getUpTime();
        void getStorageUsage();
        void getRAMUsage();
        void getCPUUsage();
        void updateResourcesInfo();

    private:
        struct sysinfo info;
        long total_ram_mb;
        long free_ram_mb;
        long buffer_ram_mb;
        long cached_ram_mb;

        struct statvfs stat;
        unsigned long total_space;
        unsigned long free_space;
        unsigned long available_space;

        FILE *proc_stat;
        unsigned long long int user, nice, system, idle, iowait, irq, softirq, total1, total2;
        unsigned long long int total_idle, total, cpu_usage;

        int setSysinfo();
        int setStatvfs();
        int setProcStat();
        

};

#endif