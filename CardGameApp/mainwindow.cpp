#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ButtonGroupWidgets->initButtons();
    ui->ButtonGroupWidgets->selectPanel(basedata::Panel::Start);
}

MainWindow::~MainWindow()
{
    delete ui;
}
