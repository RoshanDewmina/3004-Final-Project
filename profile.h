#ifndef PROFILE_H
#define PROFILE_H

#include <string>

class Profile {
private:
    int id;
    std::string name;
    int age;
    std::string gender;

public:
    Profile(int id, const std::string& name, int age, const std::string& gender);

    // Getters
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;

    // Setters
    void setName(const std::string& name);
    void setAge(int age);
    void setGender(const std::string& gender);
};

#endif // PROFILE_H

