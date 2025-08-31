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
    ui->strat->setImage(":/images/start-1.png",":/images/start-3.png",":/images/start-2.png");
    //出牌
    ui->playCard->setImage(":/images/chupai_btn-1.png",":/images/chupai_btn-3.png",":/images/chupai_btn-2.png");
    ui->playCard_2->setImage(":/images/chupai_btn-1.png",":/images/chupai_btn-3.png",":/images/chupai_btn-2.png");
    //不要
    ui->pass->setImage(":/images/pass_btn-1.png",":/images/pass_btn-3.png",":/images/pass_btn-2.png");
    //不抢
    ui->giveUp->setImage(":/images/buqiang-1.png",":/images/buqiang-3.png",":/images/buqiang-2.png");
    //1 2 3分
    ui->oneScore->setImage(":/images/1fen-1.png",":/images/1fen-3.png",":/images/1fen-2.png");
    ui->twoScore->setImage(":/images/2fen-1.png",":/images/2fen-3.png",":/images/2fen-2.png");
    ui->threeScore->setImage(":/images/3fen-1.png",":/images/3fen-3.png",":/images/3fen-2.png");
    //设置按钮大小
    QVector<MyButton*> btns;
    btns << ui->strat << ui->playCard << ui->playCard_2
         << ui->pass <<ui->giveUp << ui->oneScore<< ui->twoScore<<ui->threeScore;
    for(int i=0 ;i <btns.size();++i)
    {
        btns[i]->setFixedSize(90,45);
    }

    connect(ui->strat,&MyButton::clicked,this,&ButtonGroup::startGame);
    connect(ui->playCard,&MyButton::clicked,this,&ButtonGroup::playHand);
    connect(ui->playCard_2,&MyButton::clicked,this,&ButtonGroup::playHand);
    connect(ui->pass,&MyButton::clicked,this,&ButtonGroup::pass);
    connect(ui->giveUp,&MyButton::clicked,this,[=]()
    {
        emit betPoint(0);
    });
    connect(ui->oneScore,&MyButton::clicked,this,[=]()
    {
        emit betPoint(1);
    });
    connect(ui->twoScore,&MyButton::clicked,this,[=]()
    {
        emit betPoint(2);
    });
    connect(ui->threeScore,&MyButton::clicked,this,[=]()
    {
        emit betPoint(3);
    });
}

void ButtonGroup::selectPanel(basedata::Panel panel,int bet)
{
    int targetIndex = -1;  // 初始值设为无效索引，避免未匹配时出错
    switch (panel) {
    case basedata::Panel::Start:
        targetIndex = 0;
        break;
    case basedata::Panel::PlayCard:
        targetIndex = 1;
        break;
    case basedata::Panel::PassOrPlay:
        targetIndex = 2;
        break;
    case basedata::Panel::CallLord:
        targetIndex = 3;
        break;
    case basedata::Panel::Empty:
        targetIndex = 4;
        break;
    default:
        return;  // 直接返回，避免设置无效索引
    }
    ui->stackedWidget->setCurrentIndex(targetIndex);
    if(panel == basedata::Panel::CallLord)
    {
        if(bet == 0)
        {
            ui->oneScore->setVisible(true);
            ui->twoScore->setVisible(true);
            ui->threeScore->setVisible(true);
        }
        else if(bet == 1)
        {
            ui->oneScore->setVisible(false);
            ui->twoScore->setVisible(true);
            ui->threeScore->setVisible(true);
        }
        else if(bet == 2)
        {
            ui->oneScore->setVisible(false);
            ui->twoScore->setVisible(false);
            ui->threeScore->setVisible(true);
        }
    }
}

int ButtonGroup::getCurrentIndex()
{
    return ui->stackedWidget->currentIndex();
}
} // end of namespace pannel
