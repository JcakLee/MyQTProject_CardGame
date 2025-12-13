#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"

using namespace basedata;

namespace gamecontrol
{
class Strategy
{
public:
    Strategy(Player* player,const Cards& cards);
    //找出指定数量(count)的相同点数的牌(point)，找出count张点数为point的牌
    Cards findSamePointCards(CardPoint point,int count);
private:
    Player* m_player;
    Cards m_cards;
};
} //end of namespace gamecontrol
#endif // STRATEGY_H

