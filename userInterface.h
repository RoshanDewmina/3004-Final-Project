#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>

class UserInterface {
public:
    UserInterface();
    void displayMetrics(const std::string& metrics);
    void showRecommendations(const std::string& recommendations);
    void manageUserProfile();
};

#endif