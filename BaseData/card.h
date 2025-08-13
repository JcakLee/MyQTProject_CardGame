#ifndef CARD_H
#define CARD_H
#include "UnitType.h"
#include "BaseData.h"

namespace basedata
{
    class EXPORT_BASEDATA_ABI Card
    {
        public:
            Card();
            ~Card();

            //Get function
            CardSuit getSuit();
            CardPoint getPoint();

            //Set function
            void setPoint(CardPoint point);
            void setSuit(CardSuit suit);

        private:
            CardSuit m_suit;
            CardPoint m_point;
    };
} //end of namespace basedata


#endif // CARD_H
