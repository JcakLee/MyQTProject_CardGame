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

    CardPoint Card::getPoint() const
    {
        return m_point;
    }

    CardSuit Card::getSuit() const
    {
        return m_suit;
    }

    bool lessSort(const Card& c1, const Card& c2)
    {
        if(c1.getPoint() == c2.getPoint())
        {
            return c1.getSuit() < c2.getSuit();
        }
        else
        {
            return c1.getPoint() < c2.getPoint();
        }
    }

    bool greaterSort(const Card &c1, const Card &c2)
    {
        if(c1.getPoint() == c2.getPoint())
        {
            return c1.getSuit() > c2.getSuit();
        }
        else
        {
            return c1.getPoint() > c2.getPoint();
        }
    }

} //end of namespace basedata
