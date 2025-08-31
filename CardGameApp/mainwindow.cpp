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
    //初始化扑克牌场景
    initGameScene();

    //定时器实例化
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&MainWindow::onDispatchCard);
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
    connect(m_gameControl,&gamecontrol::GameControl::playerStatusChanged,this,&MainWindow::onPlayerStatusChanged);
    connect(m_gameControl,&gamecontrol::GameControl::notifyGrabLoadBet,this,&MainWindow::onGradLordBet);
    connect(m_gameControl,&gamecontrol::GameControl::gameStatusChanged,this,&MainWindow::gameStatusPrecess);
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
    QPixmap pixmap(":/images/card.png");
    if (pixmap.isNull()) { // 增加图片加载失败检查，避免崩溃
        qWarning() << "卡牌图片加载失败！路径：:/images/card.png";
        return;
    }
    m_cardSize.setWidth(pixmap.width() / 13);
    m_cardSize.setHeight(pixmap.height() / 5);

    // 3. 背景图
    m_cardBG = pixmap.copy(2*m_cardSize.width(), 4*m_cardSize.height(),
                                m_cardSize.width(), m_cardSize.height());
    // 正常花色
    for(int i = 0, suitInt = static_cast<int>(basedata::CardSuit::Suit_Begin) + 1;
         suitInt < static_cast<int>(basedata::CardSuit::Suit_End);
         ++suitInt, ++i)
    {
        // 将整数转换回CardSuit枚举类型
        basedata::CardSuit suit = static_cast<basedata::CardSuit>(suitInt);

        for(int j = 0, ptInt = static_cast<int>(basedata::CardPoint::CardPoint_Begin) + 1;
             ptInt < static_cast<int>(basedata::CardPoint::Card_SJ);
             ++ptInt, ++j)
        {
            // 将整数转换回CardPoint枚举类型
            basedata::CardPoint pt = static_cast<basedata::CardPoint>(ptInt);
            Card card(suit, pt);
            // 裁剪图片
            cropImage(pixmap, j*m_cardSize.width(), i*m_cardSize.height(), card);
        }
    }
    // 大小王
    Card c;
    c.setPoint(basedata::CardPoint::Card_SJ);
    c.setSuit(basedata::CardSuit::Suit_Begin);
    cropImage(pixmap, 0, 4*m_cardSize.height(), c);

    c.setPoint(basedata::CardPoint::Card_BJ);
    cropImage(pixmap, m_cardSize.width(), 4*m_cardSize.height(), c);
}

void MainWindow::cropImage(QPixmap &pixmap, int x, int y, Card &card)
{
    //裁剪当前卡牌的正面图片
    QPixmap sub = pixmap.copy(x, y, m_cardSize.width(), m_cardSize.height());
    CardPannel* panel = new CardPannel(this);
    panel->setImage(sub, m_cardBG);
    panel->setCard(card);
    panel->hide();
    m_CardMap.insert(card, panel);
    //connect(panel, &CardPanel::cardSelected, this, &MainWindow::onCardSelected);
}

void MainWindow::initButtonGroup()
{
    //按钮组初始化
    ui->ButtonGroupWidgets->initButtons();
    ui->ButtonGroupWidgets->selectPanel(basedata::Panel::Start);
    connect(ui->ButtonGroupWidgets,&ButtonGroup::startGame,this,[=](){
        //界面的初始化
        ui->ButtonGroupWidgets->selectPanel(basedata::Panel::Empty);
        m_gameControl->clearPlayerScore();
        updateScore();
        //修改游戏状态 -> 发牌
    gameStatusPrecess(basedata::GameStatus::Dispatchcard);
    });
    connect(ui->ButtonGroupWidgets,&ButtonGroup::playHand,this,[=](){});
    connect(ui->ButtonGroupWidgets,&ButtonGroup::pass,this,[=](){});
    connect(ui->ButtonGroupWidgets,&ButtonGroup::betPoint,this,[=](int bet){
    m_gameControl->getUserPlayer()->setGradPoint(bet);
    });

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

void MainWindow::initGameScene()
{
    //1.发牌区的扑克牌
    m_baseCard = new CardPannel(this);
    m_baseCard->setImage(m_cardBG,m_cardBG);
    //2.发牌过程中移动的扑克牌
    m_moveCard = new CardPannel(this);
    m_moveCard->setImage(m_cardBG,m_cardBG);
    //3.最后的三张底牌（用于窗口的显示）
    for(int i=0;i<3;++i)
    {
        CardPannel* pannel = new CardPannel(this);
        pannel->setImage(m_cardBG,m_cardBG);
        m_last3Card.push_back(pannel);
        pannel->setHidden(true);
    }
    //扑克牌的位置
    m_baseCardPos = QPoint((width() - m_cardSize.width())/2,
                           (height() - m_cardSize.height())/2 -100);
    m_baseCard->move(m_baseCardPos);
    m_moveCard->move(m_baseCardPos);
    int base = (width() - 3*m_cardSize.width() - 2*10)/2;
    for(int i = 0;i<3;++i)
    {
        m_last3Card[i]->move(base + (m_cardSize.width()+10)*i,20);
    }
}

void MainWindow::gameStatusPrecess(basedata::GameStatus status)
{
    //记录游戏状态
    m_gameStatus = status;

    //处理游戏状态
    switch (status)
    {
        case basedata::GameStatus::CallingLord:
        {
            //显示底牌数据
            CardList last3Card = m_gameControl->takeSurplusCards().toCardList();
            //给底牌窗口设置图片
            for(int i = 0;i<last3Card.size();++i)
            {
                QPixmap front = m_CardMap[last3Card.at(i)]->getImage();
                m_last3Card[i]->setImage(front,m_cardBG);
                m_last3Card[i]->hide();
            }
            m_gameControl->strartLordCard();
            break;
        }
        case basedata::GameStatus::Dispatchcard:
        {
            startDispatchCard();
            break;
        }
        case basedata::GameStatus::PlayingHand:
        {

            break;
        }
        default:
            break;
    }
}

void MainWindow::startDispatchCard()
{
    //初始化每张牌的属性
    for(auto it = m_CardMap.begin();it!=m_CardMap.end();++it)
    {
        it.value()->setIsSelected(false);
        it.value()->setFrontSide(true);
        it.value()->hide();
    }
    //隐藏三张底牌
    for(int i =0;i<m_last3Card.size();++i)
    {
        m_last3Card.at(i)->hide();
    }
    //重置玩家的窗口上下文信息
    int index = m_playerList.indexOf(m_gameControl->getUserPlayer());
    for(int i = 0;i<m_playerList.size();++i)
    {
        m_contextMap[m_playerList.at(i)].lastCard.clear();
        m_contextMap[m_playerList.at(i)].info->hide();
        m_contextMap[m_playerList.at(i)].roleImg->hide();
        m_contextMap[m_playerList.at(i)].isFrontSide = i==index ? true:false;
    }
    //重置所有玩家的卡牌数据
    m_gameControl->resetCardData();
    //显示底牌
    m_baseCard->show();
    //隐藏按钮面板
    ui->ButtonGroupWidgets->selectPanel(basedata::Panel::Empty);
    //启动定时器
    m_timer->start(10);
    //播放背景音乐
}

void MainWindow::onDispatchCard()
{
    //记录扑克牌的位置
    static int curMovePos = 0;
    //当前玩家
    Player* curPlayer = m_gameControl->getCurrentPlayer();
    if(curMovePos >= 100)
    {
        //给玩家发一张牌
        Card card = m_gameControl->takeOneCard();
        curPlayer->storeDispatchcard(card);
        Cards cards(card);
        disPosCard(curPlayer,cards);
        //切换玩家
        m_gameControl->setCurrentPlayer(curPlayer->getNextPlayer());
        curMovePos = 0;
        //发牌动画
        cardMoveStep(curPlayer,curMovePos);
        //判断牌是否发完了
        if(m_gameControl->takeSurplusCards().cardCount() == 3)
        {
            //终止定时器
            m_timer->stop();
            //切换游戏状态
            gameStatusPrecess(basedata::GameStatus::CallingLord);
            return;
        }
    }
    //移动扑克牌
    cardMoveStep(curPlayer,curMovePos);
    curMovePos += 15;

}

void MainWindow::cardMoveStep(Player* player,int curPos)
{
    //得到每个玩家的扑克牌展示区域
    QRect cardRect = m_contextMap[player].cardRect;
    //每个玩家的单元步长
    int unit[] =
    {
        (m_baseCardPos.x() - cardRect.right()) / 100,
        (cardRect.left() - m_baseCardPos.x()) / 100,
        (cardRect.top() - m_baseCardPos.y()) / 100
    };
    //每次窗口移动的时候每个玩家对应的牌实时坐标位置
    QPoint pos[] =
    {
        QPoint(m_baseCardPos.x() - curPos*unit[0],m_baseCardPos.y()),
        QPoint(m_baseCardPos.x() + curPos*unit[1],m_baseCardPos.y()),
        QPoint(m_baseCardPos.x(),  m_baseCardPos.y() + curPos*unit[2])
    };
    //移动扑克牌窗口
    int index = m_playerList.indexOf(player);
    m_moveCard->move(pos[index]);
    //临界状态处理
    if(curPos == 0)
    {
        m_moveCard->show();
    }
    if(curPos == 100)
    {
        m_moveCard->hide();
    }
}

void MainWindow::disPosCard(Player* player,const Cards& cards)
{
    Cards& myCard = const_cast<Cards&>(cards);
    CardList list = myCard.toCardList();
    for(int i =0;i<list.size();++i)
    {
        CardPannel* pannel = m_CardMap[list.at(i)];
        if(pannel != nullptr) pannel->setOwner(player);
    }
    //更新扑克牌在窗口中的显示
    updatePlayerCards(player);
}

void MainWindow::updatePlayerCards(Player *player)
{
    Cards cards = player->getCards();
    CardList list = cards.toCardList();
    //取出展示扑克牌的区域
    int cardSpace = 20;
    QRect cardsRect = m_contextMap[player].cardRect;
    for(int i=0;i<list.size();++i)
    {
        CardPannel* pannel = m_CardMap[list.at(i)];
        if(pannel == nullptr) continue;
        pannel->show();
        pannel->raise();
        pannel->setFrontSide(m_contextMap[player].isFrontSide);
        //水平或者垂直展示
        if(m_contextMap[player].align == Horizontal)
        {
            int leftx = cardsRect.left()+(cardsRect.width()-(list.size() - 1)*cardSpace - pannel->width()) /2;
            int topy = cardsRect.top() + (cardsRect.height() - m_cardSize.height()) / 2;
            if(pannel->getIsSelected()) topy -=10;
            pannel->move(leftx + cardSpace*i , topy);
        }
        else
        {
            int leftx = cardsRect.left() + (cardsRect.width() - m_cardSize.width()) / 2;
            int topy = cardsRect.top() + (cardsRect.height() - (list.size() - 1)* cardSpace - pannel->height()) / 2;
            pannel->move(leftx,topy + i*cardSpace);
        }
    }
}

void MainWindow::onPlayerStatusChanged(Player* player,basedata::PlayerStatus status)
{
    switch (status)
    {
        case basedata::PlayerStatus::ThinkingForcallLord:
        {
            if(player == m_gameControl->getUserPlayer())
            {
                ui->ButtonGroupWidgets->selectPanel(basedata::Panel::CallLord,m_gameControl->getPlayerMaxBet());
            }
             break;
        }
        case basedata::PlayerStatus::ThinkingForPlayHand:
        {

            break;
        }
        case basedata::PlayerStatus::Winning:
        {

            break;
        }
        default:
            break;
    }
}

void MainWindow::onGradLordBet(Player *player, int bet, bool flag)
{
    //显示抢地主的信息提示
    PlayerContext context = m_contextMap[player];
    QPixmap pix; // 定义 QPixmap 对象
    if(bet == 0)
    {
        if (!pix.load(":/images/buqinag.png"))
        {
            qWarning() << "图片加载失败：:/images/buqinag.png";
            return;
        }
        context.info->setPixmap(pix); // 传入 QPixmap 对象
    }
    else
    {
        if(flag)
        {
            if (!pix.load(":/images/jiaodizhu.png"))
            {
                qWarning() << "图片加载失败：:/images/jiaodizhu.png";
                return;
            }
            context.info->setPixmap(pix);
        }
        else
        {
            if (!pix.load(":/images/qiangdizhu.png"))
            {
                qWarning() << "图片加载失败：:/images/qiangdizhu.png";
                return;
            }
            context.info->setPixmap(pix);
        }
    }
    context.info->show();
}
