#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    skinContact = new Skincontact(this);
    connect(ui->activateContact, &QPushButton::clicked, this, &MainWindow::activateSkinContact);
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
    this->profiles.emplace_back(new Profile(id, name, age, gender));
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
             ui->loginText->setPlainText("");
             currentProfile = profile;
             isLoggedIn = true;
             return;
         }
     }
    ui->outputLog->setPlainText("The Id does not exist");
    ui->loginText->setPlainText("");
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
                ui->deleteID->setPlainText("");
            }
            delete profile;
            return true;
        }
        return false;
    });

    if (it != profiles.end()) {
        profiles.erase(it, profiles.end());
        ui->outputLog->setPlainText("Profile has been deleted!!!");
        ui->deleteID->setPlainText("");
    } else {
        ui->outputLog->setPlainText("ID Does not exist");
         ui->deleteID->setPlainText("");
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

void MainWindow::startScan() {
    if (!isLoggedIn) {
        ui->outputLog->setPlainText("Cannot start scan without logging in");
        return;
    }

    ui->outputLog->setPlainText("");

    if (!skinContact->getContactStatus()) {
        ui->outputLog->setPlainText("Device not in contact with skin. Activate skin contact to start the scan.");
        return;
    }

    currentPoint = 0;
    currentProfile->healthData.clear();

    // Use a loop to wait for user interaction for each scan point
    while (currentPoint < 24) {
        if (skinContact->getContactStatus()) {
            collectDataAtPoint();         // Collect data for the current point
            deactivateSkinContact();      // Automatically deactivate skin contact
            ui->outputLog->setPlainText(QString("Point %1 scanned. Activate skin contact to continue.").arg(currentPoint + 1));
            currentPoint++;

            // Wait for the user to reactivate skin contact
            while (!skinContact->getContactStatus()) {
                QCoreApplication::processEvents(); // Allow the UI to update and wait for user interaction
            }
        } else {
            ui->outputLog->setPlainText("Activate skin contact to continue scanning.");
            QCoreApplication::processEvents(); // Allow the UI to update while waiting
        }
    }

    ui->outputLog->setPlainText("Scan complete... Data collected.");
}


void MainWindow::collectDataAtPoint(){
    double value = generateRandomValue();
    currentProfile->healthData.push_back(value);
    QString text = QString("Data collected at point %1").arg(currentPoint + 1);
    ui->outputLog->setPlainText(text);
}

double MainWindow::generateRandomValue(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(5, 160);
    //QString randomNumber = QString::number(distr(gen));
    double randomNumber = distr(gen);
    return randomNumber;
}

//<-----------------Skin Contact----------------->

void MainWindow::activateSkinContact(){
    skinContact->activateContact();
    ui->skinText->setPlainText("Skin is in contact");
}

void MainWindow::deactivateSkinContact(){
    skinContact->deactivateContact();
    ui->skinText->setPlainText("Skin is not in contact");
}
