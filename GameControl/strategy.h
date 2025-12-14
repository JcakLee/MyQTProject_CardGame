#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"
#include "playhand.h"

using namespace basedata;

namespace gamecontrol
{
class Strategy
{
public:
    Strategy(Player* player,const Cards& cards);
    //找出指定数量(count)的相同点数的牌(point)，找出count张点数为point的牌
    Cards findSamePointCards(CardPoint point,int count);

    //找出所有点数数量为count的牌==>得到一个多张扑克牌数组
    QVector<Cards> findCardsByCount(int count);

    //根据点数范围找牌
    Cards getRangeCards(CardPoint begin, CardPoint end);

    //按牌型找牌，并且指定要找的牌是否要大过指定的牌型
    QVector<Cards> findCardType(PlayHand hand,bool beart);

private:
    QVector<Cards> getCards(CardPoint point, int number);
    QVector<Cards> getTripleSingleOrPair(CardPoint begin, HandType type);

private:
    Player* m_player;
    Cards m_cards;
};
} //end of namespace gamecontrol
#endif // STRATEGY_H

