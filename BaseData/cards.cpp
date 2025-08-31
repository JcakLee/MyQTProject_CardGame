#include "cards.h"
#include <QRandomGenerator>

namespace basedata
{
Cards::Cards() {}

Cards::Cards(const Card &card)
{
    addCard(card);
}

void Cards::addCard(const Card &card)
{
    m_cards.insert(card);
}

void Cards::addCard(const Cards &cards)
{
    m_cards.unite(cards.m_cards);
}

Cards &Cards::operator <<(const Card &card)
{
    addCard(card);
    return *this;
}

Cards &Cards::operator <<(const Cards &cards)
{
    addCard(cards);
    return *this;
}

void Cards::deleteCard(Card &card)
{
    m_cards.remove(card);
}

void Cards::deleteCard(Cards &cards)
{
    m_cards.subtract(cards.m_cards);
}

int Cards::cardCount()
{
    return m_cards.size();
}

bool Cards::isEmpty()
{
    return m_cards.isEmpty();
}

void Cards::clear()
{
    m_cards.clear();
}

CardPoint Cards::maxPoint()
{
    CardPoint max = CardPoint::CardPoint_Begin;
    if(!m_cards.isEmpty())
    {
        // for(auto it = m_cards.begin();it!=m_cards.end();it++)
        // {
               //Card& card = const_cast<Card&>(*it); //QSet 的迭代器返回 const 引用，因为集合元素在 C++ 中是不可修改的（修改会影响哈希值）
        //     if(it->getPoint() > max)
        //     {
        //         max = it->getPoint();
        //     }
        // }
        for(const auto& item : m_cards)
        {
            if(item.getPoint() > max) max = item.getPoint();
        }
        return max;
    }
}

CardPoint Cards::minPoint()
{
    CardPoint min = CardPoint::CardPoint_End;
    if(!m_cards.isEmpty())
    {
        for(const auto& item : m_cards)
        {
            if(item.getPoint() < min) min = item.getPoint();
        }
        return min;
    }
}

int Cards::pointCount(CardPoint point)
{
    int count = 0;
    for(const auto& item : m_cards)
    {
        if(item.getPoint() == point) count++;
    }
    return count;
}

bool Cards::containsCard(const Card &card)
{
    return m_cards.contains(card);
}

bool Cards::containsCard(const Cards &cards)
{
    return m_cards.contains(cards.m_cards);
}

Card Cards::takeRandCard()
{
    //生成随机数
    int num = QRandomGenerator::global()->bounded(m_cards.size());
    QSet<Card>::const_iterator it = m_cards.constBegin();
    for(int i = 0; i<num;i++,it++);
    Card card = *it;
    m_cards.erase(it);
    return card;
}

CardList Cards::toCardList(SortType type)
{
    CardList vec;
    for(const auto & item : m_cards)
    {
        vec << item;
    }
    if(type == SortType::ASC)
    {
        std::sort(vec.begin(),vec.end(),lessSort);
    }
    else if(type == SortType::DESC)
    {
        std::sort(vec.begin(),vec.end(),greaterSort);
    }
    else if(type == SortType::NOSORT)
    {
        //do nothing
    }
    else
    {
        // errmessage
    }

    return vec;
}

} //end of namespace basedata
