#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "profile.h"
#include "skincontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Profile Management
    void createProfile();
    void updateProfile();
    void deleteProfile();
    void loginProfile();
    Profile* getProfileById(QString id);
    QString generateRandomId();

    //Data Collection
    void startScan();
    void collectDataAtPoint();
    double generateRandomValue();

    //Skin Contact
    void activateSkinContact();
    void deactivateSkinContact();

    int currentPoint;
    Skincontact* skinContact;
    std::vector<Profile*> profiles;
    Profile* currentProfile;
    bool isLoggedIn;

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
