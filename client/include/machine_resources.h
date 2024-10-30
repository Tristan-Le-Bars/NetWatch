
#ifndef CLASS_MACHINE_RESOURCES
#define CLASS_MACHINE_RESOURCES

#include <iostream>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <mutex>

class MachineResources {
    public:
        MachineResources(std::string id);
        ~MachineResources();

        std::string getUpTime();
        void getStorageUsage();
        void getRAMUsage();
        void getCPUUsage();
        void updateResourcesInfo();
        std::string getFormattedData();

    private:
        std::string client_id;
        struct sysinfo info;
        double total_ram_mb;
        double free_ram_mb;
        double buffer_ram_mb;
        double cached_ram_mb;

        struct statvfs stat;
        double total_space;
        double free_space;
        double available_space;

        FILE *proc_stat;
        unsigned long long int user, nice, system, idle, iowait, irq, softirq, total1, total2;
        unsigned long long int total_idle, total, cpu_usage;

        int setSysinfo();
        int setStatvfs();
        int setProcStat();
        
        std::mutex resourceMutex;
};

#endif 