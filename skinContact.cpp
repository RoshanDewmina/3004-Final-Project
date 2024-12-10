#include "skincontact.h"

Skincontact::Skincontact(QObject* parent)
    : QObject(parent), isContacting(false) {}

void Skincontact::activateContact() {
    if (!isContacting) {
        isContacting = true;
        qDebug() << "Skincontact: Activated. Device is contacting the skin.";
    } else {
        qDebug() << "Skincontact: Already activated. Device is already in contact with the skin.";
    }
}

void Skincontact::deactivateContact() {
    if (isContacting) {
        isContacting = false;
        qDebug() << "Skincontact: Deactivated. Device lifted off the skin.";
    } else {
        qDebug() << "Skincontact: Already deactivated. Device is not in contact with the skin.";
    }
}

QString Skincontact::getStatus() const {
    return isContacting ? "Device is contacting the skin." : "Device is not contacting the skin.";
}

bool Skincontact::getContactStatus() {
    return isContacting;
}
