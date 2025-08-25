#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "player.h"

namespace basedata
{
class EXPORT_BASEDATA_ABI Robot : public Player
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent);
    explicit Robot(QString name ,QObject *parent = nullptr);
    void preparecallLord() override;
    void preparePlayHand() override;
};
} //end of namespace basedata

#endif // ROBOT_H
