#ifndef SKINCONTACT_H
#define SKINCONTACT_H

#include <QObject>
#include <QString>
#include <QDebug> // For debug logging

class Skincontact : public QObject {
    Q_OBJECT

public:
    explicit Skincontact(QObject* parent = nullptr);
    void activateContact();
    void deactivateContact();
    QString getStatus() const;
    bool getContactStatus();

private:
    bool isContacting = false;
};

#endif // SKINCONTACT_H
