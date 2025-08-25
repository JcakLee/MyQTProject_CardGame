#include "userplayer.h"

namespace basedata
{
UserPlayer::UserPlayer(QObject *parent) :Player(parent)
{
    m_type = PlayerType::User;
}

UserPlayer::UserPlayer(QString name, QObject *parent) : Player(name, parent)
{
    m_type = PlayerType::User;
}

void UserPlayer::preparecallLord()
{

}

void UserPlayer::preparePlayHand()
{

}
} //end of namespace basedata
