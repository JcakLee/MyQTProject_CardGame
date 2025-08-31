#include "gamecontrol.h"
#include <QRandomGenerator>//生成随机数

namespace gamecontrol
{
GameControl::GameControl(QObject *parent)
    : QObject{parent}
{}

void GameControl::initPlayer()
{
    m_robotLeft = new basedata::Robot("Robot-LEFT",this);
    m_robotRight = new basedata::Robot("Robot-RIGHT",this);
    m_userplayer = new basedata::UserPlayer("UserPlayer",this);

    //头像
    m_robotLeft->direction(PlayerDir::Left);
    m_robotRight->direction(PlayerDir::Right);
    m_userplayer->direction(PlayerDir::Right);

    //性别
    basedata::Sex sex1;
    basedata::Sex sex2;
    basedata::Sex sex3;
    sex1 = (basedata::Sex)QRandomGenerator::global()->bounded(2);
    m_robotLeft->setSex(sex1);
    sex2 = (basedata::Sex)QRandomGenerator::global()->bounded(2);
    m_robotRight->setSex(sex2);
    sex3 = (basedata::Sex)QRandomGenerator::global()->bounded(2);
    m_userplayer->setSex(sex3);


    //出牌顺序
    m_userplayer->setPrePlayer(m_robotLeft);
    m_userplayer->setNextPlayer(m_robotRight);

    m_robotLeft->setPrePlayer(m_robotRight);
    m_robotLeft->setNextPlayer(m_userplayer);

    m_robotRight->setPrePlayer(m_userplayer);
    m_robotRight->setNextPlayer(m_robotLeft);

    //指定当前玩家
    m_currentPlayer = m_robotLeft;

    //处理玩家发出的抢分信号
    connect(m_userplayer,&UserPlayer::notifyGrabLordBet,this,&GameControl::onGrabBet);
    connect(m_robotLeft,&UserPlayer::notifyGrabLordBet,this,&GameControl::onGrabBet);
    connect(m_robotRight,&UserPlayer::notifyGrabLordBet,this,&GameControl::onGrabBet);

}

Robot *GameControl::getLeftRobot()
{
    return m_robotLeft;
}

Robot *GameControl::getRightRobot()
{
    return m_robotRight;
}

UserPlayer *GameControl::getUserPlayer()
{
    return m_userplayer;
}

void GameControl::setCurrentPlayer(Player *player)
{
    m_currentPlayer = player;
}

Player *GameControl::getCurrentPlayer()
{
    return m_currentPlayer;
}

Player *GameControl::getPendPlayer()
{
    return m_pendPlayer;
}

Cards GameControl::getPendCards()
{
    return m_pendcards;
}

void GameControl::initAllCards()
{
    m_allCards.clear();
    /*大小王没有花色*/
    for(CardPoint p = CardPoint::CardPoint_Begin+1;p<CardPoint::Card_BJ;++p)
    {
        for(CardSuit s = CardSuit::Suit_Begin + 1; s < basedata::CardSuit::Suit_End;++s)
        {
            Card card(s,p);
            m_allCards.addCard(card);
        }
    }
    m_allCards.addCard(Card(CardSuit::Suit_Begin,CardPoint::Card_SJ)); //小王
    m_allCards.addCard(Card(CardSuit::Suit_Begin,CardPoint::Card_BJ)); //大王
}

Card GameControl::takeOneCard()
{
    return m_allCards.takeRandCard();
}

Cards GameControl::takeSurplusCards()
{
    return m_allCards;
}

void GameControl::resetCardData()
{
    initAllCards();
    m_robotLeft->clearCards();
    m_robotRight->clearCards();
    m_userplayer->clearCards();
    //初始化出牌玩家和出牌玩家出的牌
    m_pendPlayer = nullptr;
    m_pendcards.clear();
}

void GameControl::strartLordCard()
{
    m_currentPlayer->preparecallLord();
    emit playerStatusChanged(m_currentPlayer,basedata::PlayerStatus::ThinkingForcallLord);
}

void GameControl::becomeLord(Player* player)
{
    player->setRole(Role::Lord);
    player->getPrePlayer()->setRole(Role::Farmer);
    player->getNextPlayer()->setRole(Role::Farmer);
    m_currentPlayer = player;
    player->storeDispatchcards(m_allCards);
    QTimer::singleShot(1000,this,[=](){
        emit gameStatusChanged(basedata::GameStatus::PlayingHand);
        emit playerStatusChanged(player,basedata::PlayerStatus::ThinkingForPlayHand);
        m_currentPlayer->preparePlayHand(); //地主准备出牌
    });
}

void GameControl::clearPlayerScore()
{
    m_robotLeft->setScore(0);
    m_robotRight->setScore(0);
    m_userplayer->setScore(0);
}

void GameControl::onGrabBet(Player *player, int bet)
{
    //通知主界面玩家叫地主了，更新提示信息
    if(bet == 0 || m_betRecord.bet >= bet)
    {
        emit notifyGrabLoadBet(player,0,false);
    }
    else if(bet > 0 && m_betRecord.bet == 0)
    {
         //第一个抢地主的玩家
        emit notifyGrabLoadBet(player,bet,true);
    }
    else
    {
        //第2，3个抢地主的玩家
         emit notifyGrabLoadBet(player,bet,false);
    }

    //判断玩家下注分数是不是3分，如果是抢地主结束
    if(bet == 3)
    {
        //玩家成为地主
        becomeLord(player);
        //清空m_betRecord
        m_betRecord.reset();
        return;
    }
    //如果不是3分，则判断最高分是地主
    if(m_betRecord.bet < bet)
    {
        m_betRecord.bet = bet;
        m_betRecord.player = player;
    }
    m_betRecord.times++;
    //如果每个玩家都抢过一次地主，抢地主结束
    if( m_betRecord.times == 3)
    {
        if(m_betRecord.bet == 0)
        {
            emit gameStatusChanged(basedata::GameStatus::Dispatchcard);
        }
        else
        {
            becomeLord(player);
        }
        m_betRecord.reset();
        return;
    }
    //切换玩家，通知下一个玩家继续抢地主
    m_currentPlayer = player->getNextPlayer();
    //发送信号给主界面，告知当前状态为抢地主
    emit playerStatusChanged(m_currentPlayer,basedata::PlayerStatus::ThinkingForcallLord);
    m_currentPlayer->preparecallLord();

}

int GameControl::getPlayerMaxBet()
{
    return m_betRecord.bet;
}
} //end of namespace gamecontrol
