#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "profile.h"

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
    Profile* getProfileById(QString id);
    QString generateRandomId();

    //Data Collection
    void startScan();
    void collectDataAtPoint();
    QString generateRandomValue();

    //Skin Contact
    void activateSkinContact();
    void deactivateSkinContact();

    int currentPoint;
    bool isSkinContact;
    //std::vector<QString> healthData;
    std::vector<Profile> profiles;

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
