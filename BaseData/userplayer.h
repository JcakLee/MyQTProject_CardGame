#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <QObject>
#include "player.h"

namespace basedata
{
class UserPlayer : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit UserPlayer(QObject *parent);
    void preparecallLord() override;
    void preparePlayHand() override;
};
} //end of namespace database
#endif // USERPLAYER_H
