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
            Card(CardSuit suit,CardPoint point);
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

            // 添加小于运算符声明
            bool operator<(const Card& other) const;

        private:
            CardSuit m_suit;
            CardPoint m_point;
    };
    // 哈希函数
    inline size_t  qHash(const Card& card, size_t  seed = 0) {
        return qHash(card.getPoint(), seed) ^ qHash(card.getSuit());
    }

    // 实现小于运算符
    inline bool Card::operator<(const Card& other) const {
        // 先比较花色，如果花色不同则直接比较花色
        if (m_suit != other.m_suit) {
            return m_suit < other.m_suit;
        }
        // 花色相同则比较点数
        return m_point < other.m_point;
    }

    bool lessSort(const Card& c1, const Card& c2);
    bool greaterSort(const Card& c1, const Card& c2);
    using CardList = QVector<Card>;

} //end of namespace basedata


#endif // CARD_H
