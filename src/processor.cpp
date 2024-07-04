#include "processor.h"
#include "linux_parser.h"
#include <iostream>
#include <string>
#include "unistd.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
    std::vector<std::string> cpu_utiliztion1;
    std::vector<std::string> cpu_utiliztion2;
    cpu_utiliztion1 = LinuxParser::CpuUtilization();
    // for (auto it = cpu_utiliztion.begin(); it != cpu_utiliztion.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }
    unsigned int microsecond = 1000000;
    usleep(3 * microsecond);//sleeps for 3 second
    cpu_utiliztion2 = LinuxParser::CpuUtilization();
    unsigned long long prevIdle, previdle, previiowait, Idle, idle, iowait, PrevNonIdle, prevuser, prevnice, prevsystem, previrq, prevsoftirq, prevsteal, NonIdle, user, nice, system, irq, softirq, steal, PrevTotal, Total, totald, idled;
    previdle = stoull(cpu_utiliztion1[5]);
    idle = stoull(cpu_utiliztion2[5]);

    previiowait = stoull(cpu_utiliztion1[6]);
    iowait = stoull(cpu_utiliztion1[6]);

    prevuser = stoull(cpu_utiliztion1[2]);
    user = stoull(cpu_utiliztion2[2]);

    prevnice = stoull(cpu_utiliztion1[3]);
    nice = stoull(cpu_utiliztion2[3]);

    prevsystem = stoull(cpu_utiliztion1[4]);
    system = stoull(cpu_utiliztion2[4]);

    previrq = stoull(cpu_utiliztion1[7]);
    irq = stoull(cpu_utiliztion2[7]);

    prevsoftirq = stoull(cpu_utiliztion1[8]);
    softirq = stoull(cpu_utiliztion2[8]);

    prevsteal = stoull(cpu_utiliztion1[9]);
    steal = stoull(cpu_utiliztion2[9]);

    prevIdle = previdle + previiowait;
    Idle = idle + iowait;

    PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    NonIdle = user + nice + system + irq + softirq + steal;

    PrevTotal = prevIdle + PrevNonIdle;
    Total = Idle + NonIdle;

    totald = Total - PrevTotal;
    idled = Idle - prevIdle;

    float cpu_utilization = (static_cast<float>(totald) - idled) / totald;
    return cpu_utilization;
    //return stof(cpu_utiliztion1[2]) / 100;
}