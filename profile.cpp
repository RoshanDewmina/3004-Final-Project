#include "profile.h"

// Constructor
Profile::Profile(QString id, const QString name, QString age, QString gender)
    : id(id), name(name), age(age), gender(gender) {}

// Getters
QString Profile::getId() const { return id; }
QString Profile::getName() const { return name; }
QString Profile::getAge() const { return age; }
QString Profile::getGender() const { return gender; }

// Setters
void Profile::setName(const QString name) { this->name = name; }
void Profile::setAge(QString age) { this->age = age; }
void Profile::setGender(QString gender) { this->gender = gender; }

