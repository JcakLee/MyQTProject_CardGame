#include "card.h"


namespace basedata
{
    Card::Card()
    {

    }

    Card::~Card()
    {

    }

    void Card::setPoint(CardPoint point)
    {
        m_point = point;
    }

    void Card::setSuit(CardSuit suit)
    {
        m_suit = suit;
    }

    CardPoint Card::getPoint()
    {
        return m_point;
    }

    CardSuit Card::getSuit()
    {
        return m_suit;
    }

} //end of namespace basedata
