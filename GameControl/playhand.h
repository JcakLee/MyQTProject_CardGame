#ifndef PLAYHAND_H
#define PLAYHAND_H
#include "cards.h"
#include "UnitType.h"

using namespace basedata;
class PlayHand
{
public:
    PlayHand();
    PlayHand(Cards& cards);
    PlayHand(HandType type,CardPoint point,int cardsNum);
    //牌型判断辅助函数
    bool Hand_Pass();
    bool Hand_Single();
    bool Hand_Pair();
    bool Hand_Triple();
    bool Hand_Triple_Single();
    bool Hand_Triple_Pair();
    bool Hand_Plane();
    bool Hand_Plane_Two_Single();
    bool Hand_Plane_Pair();
    bool Hand_Seq_Pair();
    bool Hand_Seq_Single();
    bool Hand_Bomb();
    bool Hand_Bomb_Single();
    bool Hand_Bomb_Pair();
    bool Hand_Bomb_Two_Single();
    bool Hand_Bomb_Joker();
    bool Hand_Bomb_Jokers_Single();
    bool Hand_Bomb_Jokers_Pair();
    bool Hand_Bomb_Jokers_Two_Single();

    basedata::HandType getHandType();
    basedata::CardPoint getCardPoint();
    int getExtra();
    //牌型比较
    bool canBeat(const PlayHand &other);

private:
    void classify(basedata::Cards& cards);
    void judgeCardType();

private:
    HandType m_type;
    CardPoint m_point;
    int m_cardsNum;
    QVector<basedata::CardPoint> m_oneCard;
    QVector<basedata::CardPoint> m_twoCard;
    QVector<basedata::CardPoint> m_threeCard;
    QVector<basedata::CardPoint> m_fourCard;
};

#endif // PLAYHAND_H
