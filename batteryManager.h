#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

class BatteryManager {
private:
    int batteryLevel;

public:
    BatteryManager();
    void notifyLowPower() const;
    void gracefulShutdown() const;
    void updateBatteryStatus(int level);
};

#endif
