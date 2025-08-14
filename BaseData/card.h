#ifndef CARD_H
#define CARD_H
#include "UnitType.h"
#include "BaseData.h"
#include <QVector>

namespace basedata
{
    class EXPORT_BASEDATA_ABI Card
    {
        public:
            Card();
            ~Card();

            //Get function
            CardSuit getSuit() const;
            CardPoint getPoint() const;

            //Set function
            void setPoint(CardPoint point);
            void setSuit(CardSuit suit);

            // 必须添加的运算符
            bool operator==(const Card& other) const {
                return m_point == other.m_point && m_suit == other.m_suit;
            }


        private:
            CardSuit m_suit;
            CardPoint m_point;
    };
    // 哈希函数
    inline size_t  qHash(const Card& card, size_t  seed = 0) {
        return qHash(card.getPoint(), seed) ^ qHash(card.getSuit());
    }
    bool lessSort(const Card& c1, const Card& c2);
    bool greaterSort(const Card& c1, const Card& c2);
    using CardList = QVector<Card>;

} //end of namespace basedata


#endif // CARD_H
