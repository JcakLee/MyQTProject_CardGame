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
} //end of namespace gamecontrol
