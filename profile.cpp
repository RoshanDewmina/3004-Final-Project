#include "profile.h"

// Constructor
Profile::Profile(int id, const std::string& name, int age, const std::string& gender)
    : id(id), name(name), age(age), gender(gender) {}

// Getters
int Profile::getId() const { return id; }
std::string Profile::getName() const { return name; }
int Profile::getAge() const { return age; }
std::string Profile::getGender() const { return gender; }

// Setters
void Profile::setName(const std::string& name) { this->name = name; }
void Profile::setAge(int age) { this->age = age; }
void Profile::setGender(const std::string& gender) { this->gender = gender; }

