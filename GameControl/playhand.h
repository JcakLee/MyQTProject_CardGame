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
