#include "strategy.h"


namespace gamecontrol
{
    Strategy::Strategy(Player* player,const Cards& cards)
    {
        m_player = player;
        m_cards = cards;
    }

   Cards Strategy::findSamePointCards(CardPoint point,int count)
    {
       if(count < 1 || count > 4) return Cards();
       if(point == CardPoint::Card_SJ || point == CardPoint::Card_BJ)
       {
           if(count > 1) return Cards();
           Card card;
           card.setPoint(point);
           card.setSuit(CardSuit::Suit_Begin);
           if(m_cards.containsCard(card))
           {
               Cards cards;
               cards.addCard(card);
               return cards;
           }
           return Cards();
       }

       int findCount = 0;
       Cards findCards;
       for(int suit =static_cast<int>(CardSuit::Suit_Begin)+1;suit< static_cast<int>(CardSuit::Suit_End);suit++)
       {
           Card card;
           card.setPoint(point);
           card.setSuit(static_cast<CardSuit>(suit));
           if(m_cards.containsCard(card))
           {
                findCards.addCard(card);
                if(findCount == count) return findCards;
           }
       }
       return Cards();
    }

    QVector<Cards> Strategy::findCardsByCount(int count)
    {
        QVector<Cards> cardsArray;
        if(count < 1 || count > 4) return cardsArray;
        for(CardPoint point = CardPoint::Card_3; point < CardPoint::CardPoint_End;point = (CardPoint)(point+1))
        {
            if(m_cards.pointCount(point) == count)
            {
                Cards cards;
                cards << findSamePointCards(point,count);
                cardsArray << cards;
            }
        }
        return cardsArray;
    }

    Cards Strategy::getRangeCards(CardPoint begin, CardPoint end)
    {
        Cards rangeCards;
        for(CardPoint point = begin ;point < end;point = (CardPoint)(point + 1))
        {
            int count = m_cards.pointCount(point);
            Cards card = findSamePointCards(point,count);
            rangeCards << card;
        }
        return rangeCards;
    }

    QVector<Cards> Strategy::findCardType(PlayHand hand, bool beart)
    {
        HandType type = hand.getHandType();
        CardPoint point = hand.getCardPoint();
        int extra = hand.getExtra();
        CardPoint beginPoint = beart ? CardPoint(point + 1) : CardPoint::Card_3;
        switch(type)
        {
            case HandType::Hand_Single:
                return getCards(beginPoint,1);
            case HandType::Hand_Pair:
                return getCards(beginPoint,2);
            case HandType::Hand_Triple:
                return getCards(beginPoint,3);
            default:
                break;

        }
    }

    QVector<Cards> Strategy::getCards(CardPoint point, int number)
    {
        QVector<Cards> cardsArray;
        for(CardPoint pt = point; pt < CardPoint::CardPoint_End;(CardPoint)(pt + 1))
        {
            Cards cards = findSamePointCards(pt,number);
            if(!cards.isEmpty())
            {
                cardsArray << cards;
            }
        }
        return cardsArray;
    }

    QVector<Cards> Strategy::getTripleSingleOrPair(CardPoint begin, HandType type)
    {
        //找到点数相同的三张牌
        QVector<Cards> cardsFindArray = getCards(begin,3);
        if(cardsFindArray.isEmpty())
        {
            //将找到的牌从用户手中删除
            Cards remainCards = m_cards;
            remainCards.remove(cardsFindArray);
            //在剩余牌中找单牌或对子
            Strategy st(m_player,remainCards);
            QVector<Cards> cardsArryay = st.findCardType(PlayHand(type,CardPoint::CardPoint_Begin,0),false); //找到单牌或对子
            if(!cardsArryay.isEmpty())
            {
                 //将找到的牌和三张点数相同的牌进行组合
                // 确保不会越界
                int minSize = qMin(cardsFindArray.size(), cardsArryay.size());

                for(int i =0;i<minSize;++i)
                {
                    cardsFindArray[i].addCard(cardsArryay.at(i)); //每个三条需要搭配一个单牌/对子
                }
            }
            else
            {
                cardsFindArray.clear();
            }
        }
        //将最终的结果返回
        return cardsFindArray;
    }
} //end of namespace gamecontrol
