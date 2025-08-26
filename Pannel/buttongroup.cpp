#include "buttongroup.h"
#include "ui_buttongroup.h"

namespace pannel
{
ButtonGroup::ButtonGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ButtonGroup)
{
    ui->setupUi(this);
}

ButtonGroup::~ButtonGroup()
{
    delete ui;
}

void ButtonGroup::initButtons()
{
    //开始游戏
    ui->strat->setImage(":/images/._start-1.png",":/images/._start-3.png",":/images/._start-2.png");
    //出牌
    ui->playCard->setImage(":/images/._chupai_btn-1.png",":/images/._chupai_btn-3.png",":/images/._chupai_btn-2.png");
    ui->playCard_2->setImage(":/images/._chupai_btn-1.png",":/images/._chupai_btn-3.png",":/images/._chupai_btn-2.png");
    //不要
    ui->pass->setImage(":/images/._pass_btn-1.png",":/images/._pass_btn-3.png",":/images/._pass_btn-2.png");
    //不抢
    ui->giveUp->setImage(":/images/._buqiang-1.png",":/images/._buqiang-3.png",":/images/._buqiang-2.png");
    //1 2 3分
    ui->oneScore->setImage(":/images/._1fen-1.png",":/images/._1fen-3.png",":/images/._1fen-2.png");
    ui->twoScore->setImage(":/images/._2fen-1.png",":/images/._2fen-3.png",":/images/._2fen-2.png");
    ui->threeScore->setImage(":/images/._3fen-1.png",":/images/._3fen-3.png",":/images/._3fen-2.png");
    //设置按钮大小
    QVector<MyButton*> btns;
    btns << ui->strat << ui->playCard << ui->playCard_2
         << ui->pass <<ui->giveUp << ui->oneScore<< ui->twoScore<<ui->threeScore;
    for(int i=0 ;i <btns.size();++i)
    {
        btns[i]->setFixedSize(90,45);
    }
}
} // end of namespace pannel
