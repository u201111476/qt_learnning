#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include "sysinfo.h"

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();


    // SysInfo interface
public:
    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;
};

#endif // SYSINFOLINUXIMPL_H
