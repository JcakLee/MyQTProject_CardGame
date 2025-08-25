#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <QObject>
#include "player.h"

namespace basedata
{
class EXPORT_BASEDATA_ABI UserPlayer : public Player
{
    Q_OBJECT
public:
    //using Player::Player;
    explicit UserPlayer(QObject *parent);
    explicit UserPlayer(QString name ,QObject *parent = nullptr);
    void preparecallLord() override;
    void preparePlayHand() override;
};
} //end of namespace basedata
#endif // USERPLAYER_H
