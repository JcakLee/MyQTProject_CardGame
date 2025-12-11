#ifndef PLAYHAND_H
#define PLAYHAND_H
#include "cards.h"
#include "UnitType.h"

using namespace basedata;

namespace gamecontrol
{
class PlayHand
{
public:
    PlayHand();
    PlayHand(Cards& cards);
    PlayHand(HandType type,CardPoint point,int extra);
    int getExtra();

private:
    void classify(basedata::Cards& cards);
    void judgeCardType();
    //牌型判断辅助函数
    bool Hand_Pass();
    bool Hand_Single();//单牌
    bool Hand_Pair();//对子
    bool Hand_Triple();//三不带
    bool Hand_Triple_Single();//三带一
    bool Hand_Triple_Pair();//三带一对
    bool Hand_Plane();//飞机
    bool Hand_Plane_Two_Single();//飞机带两单
    bool Hand_Plane_Pair();//飞机带两对
    bool Hand_Seq_Pair();//连对
    bool Hand_Seq_Single();//顺子
    bool Hand_Bomb();//炸弹
    bool Hand_Bomb_Single();//炸弹带一单
    bool Hand_Bomb_Pair();//炸弹带对
    bool Hand_Bomb_Two_Single();//炸弹带两单
    bool Hand_Bomb_Joker();//王炸
    bool Hand_Bomb_Jokers_Single();//王炸带
    bool Hand_Bomb_Jokers_Pair();//王炸带对
    bool Hand_Bomb_Jokers_Two_Single();//王炸带两单

private:
    HandType m_type;
    CardPoint m_point;//记录点数最小的牌
    int m_extra;
    QVector<basedata::CardPoint> m_oneCard;
    QVector<basedata::CardPoint> m_twoCard;
    QVector<basedata::CardPoint> m_threeCard;
    QVector<basedata::CardPoint> m_fourCard;
};
} //End namespacae gamecontrol
#endif // PLAYHAND_H
