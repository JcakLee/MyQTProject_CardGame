#include "playhand.h"

PlayHand::PlayHand() {}

PlayHand::PlayHand(basedata::Cards &cards)
{

}

PlayHand::PlayHand(basedata::HandType type, basedata::CardPoint point, int cardsNum)
{
    //1.对卡牌进行分类：1张的，2张的，3张的，4张的有多少种
    //2.对牌型进行分类
}

void PlayHand::classify(basedata::Cards &cards)
{
    auto list = cards.toCardList();
    constexpr int num = static_cast<int>(basedata::CardPoint::CardPoint_End) - static_cast<int>(basedata::CardPoint::CardPoint_Begin);
    std::vector<int> cardRecord(num,0);
    for(int i =0;i < list.size();++i)
    {
        Card card = list.at(i);
        int index = static_cast<int>(card.getPoint()) - static_cast<int>(basedata::CardPoint::CardPoint_Begin);
        cardRecord[index]++;
    }
    m_oneCard.clear();
    m_twoCard.clear();
    m_threeCard.clear();
    m_fourCard.clear();
    for(int i =0;i<cardRecord.size();++i)
    {
        if (i <= static_cast<int>(CardPoint::CardPoint_Begin) ||
            i >= static_cast<int>(CardPoint::CardPoint_End))
        {
            throw std::out_of_range("Invalid integer value for CardPoint conversion");
        }
        basedata::CardPoint point = static_cast<basedata::CardPoint>(i);
        switch(cardRecord[i])
        {
            case 1:
            {
                m_oneCard.push_back(point);
                break;
            }
            case 2:
            {
                m_twoCard.push_back(point);
                break;
            }
            case 3:
            {
                m_threeCard.push_back(point);
                break;
            }
            case 4:
            {
                m_fourCard.push_back(point);
                break;
            }
            default:
                break;
        }
    }
}

void PlayHand::judgeCardType()
{

}

bool PlayHand::Hand_Pass()
{
    return false;
}

bool PlayHand::Hand_Single()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty()) return true;
    return false;
}

bool PlayHand::Hand_Pair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1
       &&m_threeCard.isEmpty() && m_fourCard.isEmpty()) return true;
    return false;
}

bool PlayHand::Hand_Triple()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty()
        &&m_threeCard.size() == 1 && m_fourCard.isEmpty()) return true;
    return false;
}

bool PlayHand::Hand_Triple_Single()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty()
        &&m_threeCard.size() == 1 && m_fourCard.isEmpty()) return true;
    return false;
}

bool PlayHand::Hand_Triple_Pair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1
        &&m_threeCard.size() == 1 && m_fourCard.isEmpty()) return true;
    return false;
}

bool PlayHand::Hand_Plane()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty()
        &&m_threeCard.size() == 2 && m_fourCard.isEmpty())
    {
        std::sort(m_threeCard.begin(),m_threeCard.end());
        int difference = static_cast<int>(m_threeCard[1]) - static_cast<int>(m_threeCard[0]);
        if(difference == 1 && m_threeCard[1] < basedata::CardPoint::Card_2) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Plane_Two_Single()
{
    if(m_oneCard.size() == 2 && m_twoCard.isEmpty()
        &&m_threeCard.size() == 2 && m_fourCard.isEmpty())
    {
        std::sort(m_threeCard.begin(),m_threeCard.end());
        std::sort(m_oneCard.begin(),m_oneCard.end());
        int difference = static_cast<int>(m_threeCard[1]) - static_cast<int>(m_threeCard[0]);
        if(difference == 1 && m_threeCard[1] < basedata::CardPoint::Card_2
            &&m_oneCard[0] != basedata::CardPoint::Card_SJ && m_oneCard[1] != basedata::CardPoint::Card_BJ ) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Plane_Pair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 2
        &&m_threeCard.size() == 2 && m_fourCard.isEmpty())
    {
        std::sort(m_threeCard.begin(),m_threeCard.end());
        int difference = static_cast<int>(m_threeCard[1]) - static_cast<int>(m_threeCard[0]);
        if(difference == 1 && m_threeCard[1] < basedata::CardPoint::Card_2) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Seq_Pair()
{
 return false;
}

bool PlayHand::Hand_Seq_Single()
{
 return false;
}

bool PlayHand::Hand_Bomb()
{
 return false;
}

bool PlayHand::Hand_Bomb_Single()
{
 return false;
}

bool PlayHand::Hand_Bomb_Pair()
{
 return false;
}

bool PlayHand::Hand_Bomb_Two_Single()
{
 return false;
}

bool PlayHand::Hand_Bomb_Joker()
{
 return false;
}

bool PlayHand::Hand_Bomb_Jokers_Single()
{
 return false;
}

bool PlayHand::Hand_Bomb_Jokers_Pair()
{
 return false;
}

bool PlayHand::Hand_Bomb_Jokers_Two_Single()
{
 return false;
}


