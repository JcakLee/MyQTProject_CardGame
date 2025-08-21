#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "player.h"

namespace basedata
{
class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit Robot(QObject *parent);
    void preparecallLord() override;
    void preparePlayHand() override;
};
} //end of namespace database

#endif // ROBOT_H
