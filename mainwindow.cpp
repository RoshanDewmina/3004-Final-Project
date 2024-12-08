#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "radotechsimulator.h"

#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Managing Profiles
    connect(ui->createProfile, &QPushButton::clicked, this, &MainWindow::createProfile);
    connect(ui->updateProfile, &QPushButton::clicked, this, &MainWindow::updateProfile);
    connect(ui->deleteProfile, &QPushButton::clicked, this, &MainWindow::deleteProfile);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginProfile);

    //Data Collection
    connect(ui->startScan, &QPushButton::clicked, this, &MainWindow::startScan);

    //Skin Contact
    //connect(ui->skinContact, &QPushButton::clicked, this, &MainWindow::activateSkinContact);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//<-----------------Profile Management----------------->

QString MainWindow::generateRandomId(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    QString randomNumber = QString::number(distr(gen));
    return randomNumber;
}

void MainWindow::createProfile() {
    ui->outputLog->setPlainText("");
    QString id = generateRandomId();
    QString age = ui->createAge->toPlainText();
    QString name = ui->createName->toPlainText();
    QString gender = ui->createAge->toPlainText();
    this->profiles.emplace_back(id, name, age, gender);
    QString text = QString("Profile created with id %1").arg(id);
    ui->outputLog->setPlainText(text);
    ui->createAge->setPlainText("");
    ui->createName->setPlainText("");
    ui->createGender->setPlainText("");
}

void MainWindow::loginProfile(){
    ui->outputLog->setPlainText("");
    QString inputId = ui->loginText->toPlainText();

    for (Profile* profile : profiles) {
         if (profile->getId() == inputId) {
             ui->outputLog->setPlainText("You are logged in!!!");
             currentProfile = profile;
             isLoggedIn = true;
             return;
         }
     }
    ui->outputLog->setPlainText("The Id does not exist");
}

void MainWindow::updateProfile() {
    ui->outputLog->setPlainText("");
    QString id = ui->updateID->toPlainText();
    QString newAge = ui->updateAge->toPlainText();
    QString newName = ui->updateName->toPlainText();
    QString newGender = ui->updateAge->toPlainText();

    Profile* profile = getProfileById(id);
    if (profile) {
        if (currentProfile == profile){
            if(newName == "" && newAge == "" && newGender == ""){
                ui->outputLog->setPlainText("You did not enter any new updates");
                return;
            }
            if(newName != ""){
                profile->setName(newName);
            }
            if(newAge != ""){
                profile->setAge(newAge);
            }
            if(newGender != ""){
                profile->setGender(newGender);
            }
            ui->outputLog->setPlainText("Profile has been updated!!!");
        }
        else{
            ui->outputLog->setPlainText("You can only updated your profile");
        }
    } else {
        ui->outputLog->setPlainText("ID Does not exist");
    }
    ui->updateAge->setPlainText("");
    ui->updateName->setPlainText("");
    ui->updateGender->setPlainText("");
}

void MainWindow::deleteProfile() {
    ui->outputLog->setPlainText("");
    QString id = ui->deleteID->toPlainText();

    auto it = std::remove_if(profiles.begin(), profiles.end(), [id, this](const Profile* profile) {
        if (profile->getId() == id) {
            if (currentProfile != profile) {
                ui->outputLog->setPlainText("You cannot only delete your profile");
            }
            delete profile;
            return true;
        }
        return false;
    });

    if (it != profiles.end()) {
        profiles.erase(it, profiles.end());
        ui->outputLog->setPlainText("Profile has been deleted!!!");
    } else {
        ui->outputLog->setPlainText("ID Does not exist");
    }
}

Profile* MainWindow::getProfileById(QString id) {
    for (auto& profile : profiles) {
        if (profile->getId() == id) {
            return profile;
        }
    }
    return nullptr;
}

//<-----------------Data Collection----------------->

void MainWindow::startScan(){
    if(isLoggedIn){
        ui->outputLog->setPlainText("");
        if(!isSkinContact){
            ui->outputLog->setPlainText("Device not in contact with skin. Cannot start the scan");
            return;
        }

        currentPoint = 0;
        currentProfile->healthData.clear();

        while(currentPoint < 24){
            if(isSkinContact){
                collectDataAtPoint();
                deactivateSkinContact();
                ui->outputLog->setPlainText("Activate skin contact at next point");
                currentPoint++;
            }
        }

        ui->outputLog->setPlainText("Scan complete... Data Collected...");
    }else{
        ui->outputLog->setPlainText("Cannot start scan without logging in");
    }

}

void MainWindow::collectDataAtPoint(){
    QString value = generateRandomValue();
    currentProfile->healthData.push_back(value);
    QString text = QString("Data collected at point %1 with value %2").arg(currentPoint + 1).arg(value);
    ui->outputLog->setPlainText(text);
}

QString MainWindow::generateRandomValue(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(5, 160);
    QString randomNumber = QString::number(distr(gen));
    return randomNumber;
}

//<-----------------Skin Contact----------------->

void MainWindow::activateSkinContact(){
    isSkinContact = true;
}

void MainWindow::deactivateSkinContact(){
    isSkinContact = false;
}


