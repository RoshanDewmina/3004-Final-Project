#ifndef SKINCONTACT_H
#define SKINCONTACT_H

#include <QObject>
#include <QString>

class SkinContact : public QObject {
    Q_OBJECT

public:
    SkinContact(QObject* parent = nullptr);
    void activateContact();
    /*
    use this in mainwindow:
    void MainWindow::activateSkinContact() {
        skinContact->activateContact();
    }
    void MainWindow::deactivateSkinContact() {
        skinContact->deactivateContact();
    }
    */
    void deactivateContact();
    QString getStatus() const;
signals:
    void contactStatusChanged(const QString& status);

    /*
    add something like this in mainwindow: 

    skinContact = new SkinContact(this);
    connect(skinContact, &SkinContact::contactStatusChanged, this, [this](const QString& status) {
        ui->outputLog->setPlainText(status);
    });

    
    */

private:
    bool isContacting; 
};

#endif // SKINCONTACT_H
