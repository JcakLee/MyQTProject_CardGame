#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //按钮组初始化
    ui->ButtonGroupWidgets->initButtons();
    ui->ButtonGroupWidgets->selectPanel(basedata::Panel::Start);

    //背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString bgImagePath = QString(":/images/background-%1.png").arg(num+1);
    m_bgImage.load(bgImagePath);

    //设置窗口标题
    this->setWindowTitle("Jack斗地主");
    this->setFixedSize(1000,650);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_bgImage);
}
