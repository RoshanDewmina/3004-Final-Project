#include "radotechsimulator.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

RadoTechSimulator::RadoTechSimulator()
    : currentPoint(0), isSkinContact(false) {
    std::srand(std::time(nullptr)); // Seed for random number generation
}

// Health scan functionality
void RadoTechSimulator::startScan() {
    if (!isSkinContact) {
        std::cout << "Device not in contact with skin! Cannot start scan.\n";
        return;
    }

    currentPoint = 0;
    healthData.clear();
    std::cout << "Starting health scan...\n";

    while (currentPoint < 24) {
        collectDataPoint();
    }

    std::cout << "Scan complete. Data collected:\n";
    for (size_t i = 0; i < healthData.size(); ++i) {
        std::cout << "Point " << i + 1 << ": " << healthData[i] << "\n";
    }
}

void RadoTechSimulator::setSkinContact(bool contact) {
    isSkinContact = contact;
    if (contact) {
        std::cout << "Device in contact with skin.\n";
    } else {
        std::cout << "Device lifted off skin.\n";
    }
}

void RadoTechSimulator::collectDataPoint() {
    if (!isSkinContact) {
        std::cout << "No skin contact. Unable to collect data at point " << currentPoint + 1 << ".\n";
        return;
    }

    int value = std::rand() % 101; // Simulate measurement (0-100)
    healthData.push_back(value);
    std::cout << "Collected data at point " << currentPoint + 1 << ": " << value << "\n";
    currentPoint++;
}

// User management functionality
void RadoTechSimulator::createProfile(int id, const std::string& name, int age, const std::string& gender) {
    profiles.emplace_back(id, name, age, gender);
    std::cout << "Profile created successfully.\n";
}

void RadoTechSimulator::updateProfile(int id, const std::string& name, const int age, const std::string& gender) {
    Profile* profile = getProfileById(id);
    if (profile) {
        profile->setName(name);
        profile->setAge(age);
        profile->setGender(gender);
       std::cout << "Profile updated successfully.\n";
    } else {
        std::cout << "Profile not found.\n";
    }
}

void RadoTechSimulator::deleteProfile(int id) {
    auto it = std::remove_if(profiles.begin(), profiles.end(), [id](const Profile& profile) {
        return profile.getId() == id;
    });
    if (it != profiles.end()) {
        profiles.erase(it, profiles.end());
        std::cout << "Profile deleted successfully.\n";
    } else {
        std::cout << "Profile not found.\n";
    }
}

void RadoTechSimulator::displayProfiles() const {
    std::cout << "User Profiles:\n";
    for (const auto& profile : profiles) {
        std::cout << "ID: " << profile.getId()
                  << ", Name: " << profile.getName()
                  << ", Age: " << profile.getAge()
                  << ", Gender: " << profile.getGender() << '\n';
    }
}

Profile* RadoTechSimulator::getProfileById(int id) {
    for (auto& profile : profiles) {
        if (profile.getId() == id) {
            return &profile;
        }
    }
    return nullptr;
}
