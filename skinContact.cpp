#include "SkinContact.h"

SkinContact::SkinContact(QObject* parent)
    : QObject(parent), isContacting(false) {}

void SkinContact::activateContact() {
    if (!isContacting) {
        isContacting = true;
        emit contactStatusChanged("Device is contacting skin");
    } else {
        emit contactStatusChanged("Device is already in contact with skin");
    }
}

void SkinContact::deactivateContact() {
    if (isContacting) {
        isContacting = false;
        emit contactStatusChanged("Device lifted off the skin.");
    } else {
        emit contactStatusChanged("Device is not in contact with the skin.");
    }
}

QString SkinContact::getStatus() const {
    return isContacting ? "Device is contacting the skin." : "Device is not contacting the skin.";
}
