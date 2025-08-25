#include "robot.h"

namespace basedata
{
Robot::Robot(QObject *parent) : Player(parent)
{
    m_type = PlayerType::Robot;
}

Robot::Robot(QString name, QObject *parent) : Player(name,parent)
{
    m_type = PlayerType::Robot;
}

void Robot::preparecallLord()
{

}

void Robot::preparePlayHand()
{

}
} //end of namespace basedata
