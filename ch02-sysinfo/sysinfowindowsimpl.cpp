#include "sysinfowindowsimpl.h"
#include<Windows.h>

SysInfoWindowsImpl::SysInfoWindowsImpl():
    SysInfo (),
    m_CpuLoadLastValues()
{

}

void SysInfoWindowsImpl::init()
{
    m_CpuLoadLastValues=cpuRawData();
}

double SysInfoWindowsImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample=m_CpuLoadLastValues;
    QVector<qulonglong> secondSample=cpuRawData();
    m_CpuLoadLastValues=secondSample;
    qulonglong currentIdle=secondSample[0]-firstSample[0];
    qulonglong currentKernel=secondSample[1]-firstSample[1];
    qulonglong currentUser=secondSample[2]-firstSample[2];
    qulonglong currentSystem=currentKernel+currentUser;
    double percent=(currentSystem-currentIdle)*100.0/currentSystem;
    return qBound(0.0,percent,100.0);
}

double SysInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength=sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    qulonglong memoryPhysicalUsed=memoryStatus.ullTotalPhys-memoryStatus.ullAvailPhys;
    return static_cast<double>(memoryPhysicalUsed)/static_cast<double>(memoryStatus.ullTotalPhys)*100.0;
}

QVector<qulonglong> SysInfoWindowsImpl::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
    GetSystemTimes(&idleTime,&kernelTime,&userTime);
    QVector<qulonglong> rawData;
    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFileTime(userTime));
    return rawData;
}

qulonglong SysInfoWindowsImpl::convertFileTime(const FILETIME &filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart=filetime.dwLowDateTime;
    largeInteger.HighPart=filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}
