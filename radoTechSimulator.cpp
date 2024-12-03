#include "RaDoTechSimulator.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

RaDoTechSimulator::RaDoTechSimulator() 
    : currentPoint(0), isSkinContact(false) {
    std::srand(std::time(nullptr)); // Seed for random number generation
}

// Health scan functionality
void RaDoTechSimulator::startScan() {
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

void RaDoTechSimulator::setSkinContact(bool contact) {
    isSkinContact = contact;
    if (contact) {
        std::cout << "Device in contact with skin.\n";
    } else {
        std::cout << "Device lifted off skin.\n";
    }
}

void RaDoTechSimulator::collectDataPoint() {
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
void RaDoTechSimulator::createProfile(int id, const std::string& name, int age, const std::string& gender) {
    profiles.emplace_back(id, name, age, gender);
    std::cout << "Profile created successfully.\n";
}

void RaDoTechSimulator::updateProfile(int id, const std::string& name, int age, const std::string& gender) {
    Profile* profile = getProfileById(id);
    if (profile) {
        profile->name = name;
        profile->age = age;
        profile->gender = gender;
       std::cout << "Profile updated successfully.\n";
    } else {
        std::cout << "Profile not found.\n";
    }
}

void RaDoTechSimulator::deleteProfile(int id) {
    auto it = std::remove_if(profiles.begin(), profiles.end(), [id](const Profile& profile) {
        return profile.id == id;
    });
    if (it != profiles.end()) {
        profiles.erase(it, profiles.end());
        std::cout << "Profile deleted successfully.\n";
    } else {
        std::cout << "Profile not found.\n";
    }
}

void RaDoTechSimulator::displayProfiles() const {
    std::cout << "User Profiles:\n";
    for (const auto& profile : profiles) {
        std::cout << "ID: " << profile.id
                  << ", Name: " << profile.name
                  << ", Age: " << profile.age
                  << ", Gender: " << profile.gender << '\n';
    }
}

RaDoTechSimulator::Profile* RaDoTechSimulator::getProfileById(int id) {
    for (auto& profile : profiles) {
        if (profile.id == id) {
            return &profile;
        }
    }
    return nullptr;
}
