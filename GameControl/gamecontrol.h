#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "robot.h"
#include "userplayer.h"
#include <QObject>

using namespace basedata;
namespace gamecontrol
{
class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(QObject *parent = nullptr);

    //玩家控制相关
    void initPlayer();//初始化玩家
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();
    void setCurrentPlayer(Player* player); //设置当前玩家
    Player* getCurrentPlayer();//获取当前玩家
    Player* getPendPlayer();//获取出牌玩家
    Cards getPendCards();//获取当前玩家打出的牌

    //卡牌控制相关
    void initAllCards();//单张卡牌对象放到m_allCards中

    //发牌
    Card takeOneCard();

    //最后三张底牌
    Cards takeSurplusCards();

    //洗牌
    void resetCardData();

    //准备叫地主
    void strartLordCard();

    //成为地主
    void becomeLord(Player* player);

    //处理叫地主

    //处理出牌

    //清空玩家得分
    void clearPlayerScore();


private:
    Robot* m_robotLeft;
    Robot* m_robotRight;
    UserPlayer* m_userplayer;
    Player* m_currentPlayer;//当前玩家
    Cards m_pendcards;//当前玩家打出的牌
    Player* m_pendPlayer;
    Cards m_allCards;

};

} //end of namespace gamecontrol
#endif // GAMECONTROL_H
