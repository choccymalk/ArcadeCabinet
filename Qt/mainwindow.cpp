// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QDir>
#include <QDebug>
#include <QSysInfo>
#include <QOperatingSystemVersion>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchMame(std::string game) {
    #if (defined (_WIN32) || defined (_WIN64))
        std::string gamePathPart1 = ".\\mame\\mame.exe nes -cart mame\\roms\\";
        std::string gamePathPart2 = game;
        std::string gamePathPart3 = ".nes -skip_gameinfo";
        std::string fullGamePath = gamePathPart1+gamePathPart2+gamePathPart3;
        system(fullGamePath.c_str());
    #elif (defined (LINUX) || defined (__linux__))
        std::string gamePathPart1 = "./mame/mame.exe nes -cart mame/roms/";
        std::string gamePathPart2 = game;
        std::string gamePathPart3 = ".nes -skip_gameinfo";
        std::string fullGamePath = gamePathPart1+gamePathPart2+gamePathPart3;
        system(fullGamePath.c_str());
    #endif
}

void MainWindow::initializeUI()
{
    // Set initial focus
    ui->label_2->setPixmap(QPixmap("images/SHHS70001200px (3).png"));
    focusNextButton(0);
    colorButton(true, 1);
    currentButton = ui->pushButton;
    currentButton->setFocus();
    updateLabel();
    updatePreviewImage();
}

void MainWindow::updatePreviewImage()
{
    QString imagePath;
    if (currentButton == ui->pushButton) imagePath = getImagePath("pacman");
    else if (currentButton == ui->pushButton_2) imagePath = getImagePath("contra");
    else if (currentButton == ui->pushButton_3) imagePath = getImagePath("dk");
    else if (currentButton == ui->pushButton_4) imagePath = getImagePath("galaga");
    else if (currentButton == ui->pushButton_5) imagePath = getImagePath("smb1");
    else if (currentButton == ui->pushButton_6) imagePath = getImagePath("tetris");
    else if (currentButton == ui->pushButton_7) imagePath = getImagePath("excitebike");

    qDebug() << "Loading image from path:" << imagePath;  // Debug output

    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image, trying to load no-image.png";  // Debug output
        pixmap = QPixmap(getImagePath("no-image"));
        if (pixmap.isNull()) {
            qDebug() << "Failed to load no-image.png as well";  // Debug output
            return;
        }
    }

    qDebug() << "Pixmap size:" << pixmap.size();  // Debug output
    ui->label->setPixmap(pixmap);
    ui->label->setScaledContents(true);
    ui->label->update();  // Force update
}

QString MainWindow::getImagePath(const QString& game)
{
    QString path = QDir::currentPath() + "/images/" + game.toLower() + ".png";
    qDebug() << "Full image path:" << path;  // Debug output
    return path;
}

void MainWindow::colorButton(bool enable, int index){
    if(enable){
        if (index == 1) ui->pushButton->setStyleSheet("background-color: #531516");
        else if (index == 2) ui->pushButton_2->setStyleSheet("background-color: #531516");
        else if (index == 3) ui->pushButton_3->setStyleSheet("background-color: #531516");
        else if (index == 4) ui->pushButton_4->setStyleSheet("background-color: #531516");
        else if (index == 5) ui->pushButton_5->setStyleSheet("background-color: #531516");
        else if (index == 6) ui->pushButton_6->setStyleSheet("background-color: #531516");
        else if (index == 7) ui->pushButton_7->setStyleSheet("background-color: #531516");
    } else {
        if (index == 1) ui->pushButton->setStyleSheet("background-color: #3f3f3f");
        else if (index == 2) ui->pushButton_2->setStyleSheet("background-color: #3f3f3f");
        else if (index == 3) ui->pushButton_3->setStyleSheet("background-color: #3f3f3f");
        else if (index == 4) ui->pushButton_4->setStyleSheet("background-color: #3f3f3f");
        else if (index == 5) ui->pushButton_5->setStyleSheet("background-color: #3f3f3f");
        else if (index == 6) ui->pushButton_6->setStyleSheet("background-color: #3f3f3f");
        else if (index == 7) ui->pushButton_7->setStyleSheet("background-color: #3f3f3f");
    }
}

void MainWindow::focusNextButton(int index)
{
    qDebug() << "Focusing button with index:" << index;  // Debug output

    switch (index) {
    case 0: currentButton = ui->pushButton; break;
    case 1: currentButton = ui->pushButton_2; break;
    case 2: currentButton = ui->pushButton_3; break;
    case 3: currentButton = ui->pushButton_4; break;
    case 4: currentButton = ui->pushButton_5; break;
    case 5: currentButton = ui->pushButton_6; break;
    case 6: currentButton = ui->pushButton_7; break;
    }

    if (currentButton) {
        currentButton->setFocus();
        updateLabel();
        updatePreviewImage();
    }
}

void MainWindow::updateLabel()
{
    QString title;
    if (currentButton == ui->pushButton) title = "Pac Man";
    else if (currentButton == ui->pushButton_2) title = "Contra";
    else if (currentButton == ui->pushButton_3) title = "Donkey Kong";
    else if (currentButton == ui->pushButton_4) title = "Galaga";
    else if (currentButton == ui->pushButton_5) title = "Super Mario Bros";
    else if (currentButton == ui->pushButton_6) title = "Tetris";
    else if (currentButton == ui->pushButton_7) title = "Excitebike";

    setWindowTitle(title);
}

int MainWindow::getCurrentButtonIndex()
{
    if (currentButton == ui->pushButton) return 0;
    if (currentButton == ui->pushButton_2) return 1;
    if (currentButton == ui->pushButton_3) return 2;
    if (currentButton == ui->pushButton_4) return 3;
    if (currentButton == ui->pushButton_5) return 4;
    if (currentButton == ui->pushButton_6) return 5;
    if (currentButton == ui->pushButton_7) return 6;
    return 0;
}

// Button click handlers
void MainWindow::on_pushButton_clicked()
{
    launchMame("pacman");
}

void MainWindow::on_pushButton_2_clicked()
{
    launchMame("contra");
}

void MainWindow::on_pushButton_3_clicked()
{
    launchMame("dk");
}

void MainWindow::on_pushButton_4_clicked()
{
    launchMame("galaga");
}

void MainWindow::on_pushButton_5_clicked()
{
    launchMame("smb1");
}

void MainWindow::on_pushButton_6_clicked()
{
    launchMame("tetris");
}

void MainWindow::on_pushButton_7_clicked()
{
    launchMame("excitebike");
}
