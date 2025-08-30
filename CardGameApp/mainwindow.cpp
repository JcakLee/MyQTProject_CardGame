#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QRandomGenerator>
#include <qlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString bgImagePath = QString(":/images/background-%1.png").arg(num+1);
    m_bgImage.load(bgImagePath);

    //设置窗口标题
    this->setWindowTitle("Jack斗地主");
    this->setFixedSize(1000,650);
    //实例化游戏控制类对象
    gameControlInit();
    //更新玩家得分
    updateScore();
    //切割游戏图片
    initCardMap();
    //初始化游戏中的按钮组
    initButtonGroup();
    //初始化玩家在窗口中的上下文
    initPlayerContext();
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

void MainWindow::initButtonGroup()
{
    //按钮组初始化
    ui->ButtonGroupWidgets->initButtons();
    ui->ButtonGroupWidgets->selectPanel(basedata::Panel::Start);
    connect(ui->ButtonGroupWidgets,&ButtonGroup::startGame,this,[=](){});
    connect(ui->ButtonGroupWidgets,&ButtonGroup::playHand,this,[=](){});
    connect(ui->ButtonGroupWidgets,&ButtonGroup::pass,this,[=](){});
    connect(ui->ButtonGroupWidgets,&ButtonGroup::betPoint,this,[=](){});

}

void MainWindow::initPlayerContext()
{
    //1.放置玩家扑克牌的区域
    QRect cardsRect[] =
    {
        //x,y,width,height
        QRect(90,130,100,height()-200),  //左侧机器人
        QRect(rect().right()-190,130,100,height()-200), //右侧机器人
        QRect(250,rect().bottom() - 120,width() - 500,100) //当前玩家
    };
    //2.玩家出牌的区域
    QRect playHandRect[] =
    {
        QRect(260,150,100,100),
        QRect(rect().right() - 360,150,100,100),
        QRect(150,rect().bottom() - 290,width() - 300,100)
    };
    //3.玩家头像显示的位置
    QPoint roleImgPos[] =
    {
        QPoint(cardsRect[0].left() - 80,cardsRect[0].height()/2+20),
        QPoint(cardsRect[1].right()+10,cardsRect[1].height()/2+20),
        QPoint(cardsRect[2].right()-10,cardsRect[2].top() - 10)
    };

    int index = m_playerList.indexOf(m_gameControl->getUserPlayer());
    for(int i =0;i<m_playerList.size();++i)
    {
        PlayerContext context;
        context.align = i==index ? Horizontal : Vertical;
        context.isFrontSide = i==index ? true : false;
        context.cardRect = cardsRect[i];
        context.playHandRect = playHandRect[i];
        context.info =new QLabel(this);
        context.info->resize(160,98);
        context.info->hide();
        //显示到出牌区域的中心位置
        QRect rect = playHandRect[i];
        QPoint pt(rect.left() + (rect.width()-context.info->width())/2,
                  rect.top()+(rect.height() - context.info->height())/2);
        context.info->move(pt);
        //玩家头像
        context.roleImg = new QLabel(this);
        context.roleImg->resize(84,120);
        context.roleImg->hide();
        context.roleImg->move(roleImgPos[i]);
        m_contextMap.insert(m_playerList.at(i),context);
    }

}
