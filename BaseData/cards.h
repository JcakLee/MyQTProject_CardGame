#ifndef CARDS_H
#define CARDS_H
#include <QSet>
#include "card.h"
#include "UnitType.h"
#include "BaseData.h"

namespace basedata
{
class EXPORT_BASEDATA_ABI Cards
{
public:
    Cards();
    Cards(const Card& card);

    //添加单张卡牌
    void addCard(const Card& card);
    //添加多张卡牌
    void addCard(const Cards& cards);

    Cards& operator <<(const Card& card);
    Cards& operator <<(const Cards& cards);


    //删除单张卡牌
    void deleteCard(Card& card);
    //添加多张卡牌
    void deleteCard(Cards& cards);

    //卡牌数量
    int cardCount();

    //卡牌数量是否为空
    bool isEmpty();

    //清空卡牌
    void clear();

    //最大点数
    CardPoint maxPoint();
    //最小点数
    CardPoint minPoint();

    //指定点数的卡牌的数量
    int pointCount(CardPoint point);

    //判断某张牌是否在集合中
    bool containsCard(const Card& card);

    //判断某些牌是否在集合中
    bool containsCard(const Cards& cards);

    //随机取出一张卡牌
    Card takeRandCard();

    //QSet -> QVector
    //无序 -> 有序
    CardList toCardList(SortType type = basedata::SortType::DESC);


private:
    QSet<Card> m_cards;

};
} //end of namespace basedata

#endif // CARDS_H
