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

    gameControlInit();

    //更新玩家得分
    updateScore();
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

void MainWindow::gameControlInit()
{
    //初始化游戏控制类
    m_gameControl = new gamecontrol::GameControl(this);
    m_gameControl->initPlayer(); //初始化玩家；
    //获取三个玩家的实例化对象并存储
    Robot* robotLeft = m_gameControl->getLeftRobot();
    Robot* robotRight = m_gameControl->getRightRobot();
    UserPlayer* userPlayer = m_gameControl->getUserPlayer();
    m_playerList << robotLeft << robotRight << userPlayer;
}

void MainWindow::updateScore()
{
    int leftScore = m_playerList[0]->getScore();
    int rightScore = m_playerList[1]->getScore();
    int userScore = m_playerList[2]->getScore();
    ui->ScorePannel->setScore(leftScore,rightScore,userScore);
}

void MainWindow::initCardMap()
{
    //加载大图
    QPixmap cardBigImage(":/images/card.png");
    if (cardBigImage.isNull()) { // 增加图片加载失败检查，避免崩溃
        qWarning() << "卡牌图片加载失败！路径：:/images/card.png";
        return;
    }
    m_cardSize.setWidth(cardBigImage.width() / 13);
    m_cardSize.setHeight(cardBigImage.height() / 5);
    if (m_cardSize.width() <= 0 || m_cardSize.height() <= 0)
    { // 避免无效尺寸
        qWarning() << "卡牌尺寸计算错误！整图尺寸：" << cardBigImage.size();
        return;
    }

    //卡牌背景图
    m_cardBG = cardBigImage.copy(2*m_cardSize.width(),
                                 4*m_cardSize.height(),
                                 m_cardSize.width(),
                                 m_cardSize.height());
    //正常花色
    for (basedata::CardSuit suit = basedata::CardSuit::Suit_Begin; suit < basedata::CardSuit::Suit_End; ++suit)
    {
        // 每次切换花色时，重置点数为 CardPoint_Begin 的下一个值（Card_3）
        for (basedata::CardPoint point = basedata::CardPoint::CardPoint_Begin;point < basedata::CardPoint::Card_SJ; ++point)
        {
            // 计算当前卡牌在整张大图中的坐标（关键：对应图片的行列）
            // - 列：point 的索引（Card_3 是第1列，对应 x = 0 * 宽度）
            // - 行：suit 的索引（Diamond 是第1行，对应 y = 0 * 高度）
            int x = static_cast<int>(point) - static_cast<int>(basedata::CardPoint::CardPoint_Begin);
            int y = static_cast<int>(suit) - static_cast<int>(basedata::CardSuit::Suit_Begin);
            // 创建 Card 对象（当前花色+点数）
            basedata::Card currentCard(suit, point);
            cropImage(cardBigImage,x,y,currentCard);
        }
    }

    //大小王
    QPixmap sjFront = cardBigImage.copy(0,4*m_cardSize.height(),m_cardSize.width(),m_cardSize.height());
    if (!sjFront.isNull())
    {
        basedata::Card sjCard(basedata::CardSuit::Suit_End, basedata::CardPoint::Card_SJ);
        CardPannel* sjPannel = new CardPannel(this);
        sjPannel->setImage(sjFront, m_cardBG);
        sjPannel->setCard(sjCard);
        sjPannel->setHidden(true);
        m_CardMap.insert(sjCard, sjPannel);
    }

    QPixmap djFront = cardBigImage.copy(m_cardSize.width(),4*m_cardSize.height(),m_cardSize.width(),m_cardSize.height());
    if (!djFront.isNull())
    {
        basedata::Card djCard(basedata::CardSuit::Suit_End, basedata::CardPoint::Card_SJ);
        CardPannel* djPannel = new CardPannel(this);
        djPannel->setImage(djFront, m_cardBG);
        djPannel->setCard(djCard);
        djPannel->setHidden(true);
        m_CardMap.insert(djCard, djPannel);
    }


}

void MainWindow::cropImage(QPixmap &pixmap, int x, int y, Card &card)
{
    //裁剪当前卡牌的正面图片
    QPixmap cardFront = pixmap.copy(x * m_cardSize.width(), y * m_cardSize.height(),m_cardSize.width(),m_cardSize.height());
    //卡牌面板
    CardPannel* pannel = new CardPannel(this);
    pannel->setImage(cardFront,m_cardBG);
    pannel->setCard(card);
    pannel->setHidden(true);
    m_CardMap.insert(card,pannel);


}
