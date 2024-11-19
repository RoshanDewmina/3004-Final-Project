#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <string>

class UserProfile {
private:
    std::string name;
    int age;
    std::string gender;

public:
    UserProfile();
    UserProfile(const std::string& name, int age, const std::string& gender);
    void createProfile();
    void updateProfile(const std::string& name, int age, const std::string& gender);
    void deleteProfile();
    void displayProfile() const;
};

#endif
