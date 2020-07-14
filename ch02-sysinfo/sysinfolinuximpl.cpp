#include "sysinfolinuximpl.h"

#include <sys/types.h>
#include <sys/sysinfo.h>

SysInfoLinuxImpl::SysInfoLinuxImpl():
    SysInfo ()
{

}


void SysInfoLinuxImpl::init()
{
}

double SysInfoLinuxImpl::cpuLoadAverage()
{
}

double SysInfoLinuxImpl::memoryUsed()
{
    struct sysinfo memInfo;
}
