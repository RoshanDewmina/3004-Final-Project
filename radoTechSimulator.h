#ifndef RADOTECHSIMULATOR_H
#define RADOTECHSIMULATOR_H

#include <vector>
#include <string>
#include "profile.h"

class RaDoTechSimulator {
private:

    int currentPoint;
    bool isSkinContact;
    std::vector<int> healthData;
    std::vector<Profile> profiles;

public:
    RaDoTechSimulator();

    // Health scan functionality
    void startScan();
    void setSkinContact(bool contact);

    // User management functionality
    void createProfile(int id, const std::string& name, int age, const std::string& gender);
    void updateProfile(int id, const std::string& name, int age, const std::string& gender);
    void deleteProfile(int id);
    void displayProfiles() const;

private:
    void collectDataPoint();
    Profile* getProfileById(int id);
};

#endif // RADOTECHSIMULATOR_H
