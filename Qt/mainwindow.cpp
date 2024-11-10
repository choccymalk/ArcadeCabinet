#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void launchMame(std::string game){
    std::string gamePathPart1 = ".\\mame\\mame.exe nes -cart mame\\roms\\";
    std::string gamePathPart2 = game;
    std::string gamePathPart3 = ".nes -skip_gameinfo";
    std::string fullGamePath = gamePathPart1+gamePathPart2+gamePathPart3;
    system(fullGamePath.c_str());
    //printf(fullGamePath.c_str());
}

void MainWindow::on_pushButton_clicked()
{
    launchMame("castlevania");
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

void MainWindow::on_pushButton_8_clicked()
{
    launchMame("pacman");
}

void MainWindow::on_pushButton_9_clicked()
{
    launchMame("Mario Bros. (U) (e-Reader) [!].nes");
}

