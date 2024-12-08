#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <QMainWindow>

class Profile {
private:
    QString id;
    QString name;
    QString age;
    QString gender;

public:
    Profile(QString id, QString name, QString age, QString gender);

    std::vector<QString> healthData;
    // Getters
    QString getId() const;
    QString getName() const;
    QString getAge() const;
    QString getGender() const;
    std::vector<QString> getHealthData();

    // Setters
    void setName(const QString name);
    void setAge(QString age);
    void setGender(const QString gender);
};

#endif // PROFILE_H

