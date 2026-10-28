#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->bottom,&Bottom::changeToHome,this,&MainWindow::recvToHome);
    connect(ui->bottom,&Bottom::changeToSetting,this,&MainWindow::recvToSetting);
    connect(ui->bottom,&Bottom::changeToAir,this,&MainWindow::recvToAir);
    connect(ui->home,&HomeScreen::changeToTheme,this,&MainWindow::recvToSetting);
    connect(ui->theme,&Theme::sendThemePath,this,&MainWindow::setThemeBackground);
    connect(ui->home,&HomeScreen::changeToIcon,this,&MainWindow::recvToIcon);
    connect(ui->home,&HomeScreen::changeToMap,this,&MainWindow::recvToMap);
    connect(ui->map,&Map::backToHome,this,&MainWindow::recvToHome);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvToHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::recvToSetting()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::recvToAir()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::setThemeBackground(QString path)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->home->setBackgroundImg(path);


}

void MainWindow::recvToIcon()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::recvToMap()
{
    ui->stackedWidget->setCurrentIndex(4);
}

