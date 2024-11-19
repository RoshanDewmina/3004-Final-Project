#ifndef HEALTHSCAN_H
#define HEALTHSCAN_H

#include <vector>

class HealthScan {
private:
    int scanId;
    std::vector<double> rawData;

public:
    HealthScan();
    void performScan();
    void saveScanData();
    const std::vector<double>& getRawData() const;
};

#endif