#include "player.h"

namespace basedata
{
Player::Player(QObject *parent)
{

}

Player::Player(QString name, QObject *parent) : m_name(name)
{

}

void Player::setName(QString name)
{
    m_name = name;
}

QString Player::getName()
{
    return m_name;
}

void Player::setRole(Role role)
{
    m_role = role;
}

Role Player::getRole()
{
    return m_role;
}

void Player::setSex(Sex sex)
{
    m_sex = sex;
}

Sex Player::getSex()
{
    return m_sex;
}

void Player::direction(PlayerDir dir)
{
    m_dir = dir;
}

PlayerDir Player::getDirection()
{
    return m_dir;
}

void Player::setType(PlayerType type)
{
    m_type = type;
}

PlayerType Player::getType()
{
    return m_type;
}

void Player::setScore(int score)
{
    m_score = score;
}

int Player::getScore()
{
    return m_score;
}

void Player::setWin(bool win)
{
    m_isWin = win;
}

bool Player::getWin()
{
    return m_isWin;
}

void Player::setPrePlayer(Player *player)
{
    m_PrePlayer = player;
}

Player *Player::getPrePlayer()
{
    return m_PrePlayer;
}

void Player::setNextPlayer(Player *player)
{
    m_NextPlayer = player;
}

Player *Player::getNextPlayer()
{
    return m_NextPlayer;
}

void Player::setGradPoint(int point)
{

}

int Player::getPoint()
{
    return m_gradPoint;
}

void Player::storeDispatchcard(Card &card)
{
    m_cards.addCard(card);
}

void Player::storeDispatchcards(Cards &cards)
{
    m_cards.addCard(cards);
}

Cards Player::getCards()
{
    return m_cards;
}

void Player::clearCards()
{
    m_cards.clear();
}

void Player::playHand(Cards &cards)
{
    m_cards.deleteCard(cards);
}

void Player::setPandInfo(Player *player, Cards cards)
{
    m_PendCards = cards;
    m_Pendplayer = player;
}

Player *Player::getPandPlayer()
{
    return m_Pendplayer;
}

Cards Player::getPandCards()
{
    return m_PendCards;
}

void Player::preparecallLord()
{

}

void Player::preparePlayHand()
{

}






} //end of namespace database


