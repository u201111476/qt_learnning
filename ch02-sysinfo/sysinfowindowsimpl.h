#ifndef SYSINFOWINDOWSIMPL_H
#define SYSINFOWINDOWSIMPL_H

#include <QtGlobal>
#include <QVector>
#include "sysinfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoWindowsImpl : public SysInfo
{
public:
    SysInfoWindowsImpl();
    void init() override;
    double cpuLoadAverage() override;

    // SysInfo interface
public:
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();
    qulonglong convertFileTime(const FILETIME& filetime) const;
private:
    QVector<qulonglong> m_CpuLoadLastValues;
};

#endif // SYSINFOWINDOWSIMPL_H
