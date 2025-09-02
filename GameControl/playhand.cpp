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
    m_type = basedata::HandType::Hand_Unknown;
    m_point = basedata::CardPoint::CardPoint_Begin;
    m_cardsNum = 0;
    if(Hand_Single())
    {
        m_type = basedata::HandType::Hand_Single;
        m_point = m_oneCard[0];
    }
    else if(Hand_Pass())
    {
        m_type = basedata::HandType::Hand_Pass;
    }
    else if(Hand_Pair())
    {
        m_type = basedata::HandType::Hand_Pair;
        m_point = m_twoCard[0];
    }
    else if(Hand_Triple())
    {
        m_type = basedata::HandType::Hand_Triple;
        m_point = m_threeCard[0];
    }
    else if(Hand_Triple_Single())
    {
        m_type = basedata::HandType::Hand_Triple_Single;
        m_point = m_threeCard[0];
    }
    else if(Hand_Triple_Pair())
    {
        m_type = basedata::HandType::Hand_Triple_Pair;
        m_point = m_threeCard[0];
    }
    else if(Hand_Plane())
    {
        m_type = basedata::HandType::Hand_Plane;
        m_point = m_threeCard[0];
    }
    else if(Hand_Plane_Two_Single())
    {
        m_type = basedata::HandType::Hand_Plane_Two_Single;
        m_point = m_threeCard[0];
    }
    else if(Hand_Plane_Pair())
    {
        m_type = basedata::HandType::Hand_Plane_Pair;
        m_point = m_threeCard[0];
    }
    else if(Hand_Seq_Pair())
    {
        m_type = basedata::HandType::Hand_Seq_Pair;
        m_point = m_twoCard[0];
        m_cardsNum = m_twoCard.size();
    }
    else if(Hand_Seq_Single())
    {
        m_type = basedata::HandType::Hand_Seq_Single;
        m_point = m_oneCard[0];
        m_cardsNum = m_oneCard.size();
    }
    else if(Hand_Bomb())
    {
        m_type = basedata::HandType::Hand_Bomb;
        m_point = m_fourCard[0];
    }
    else if(Hand_Bomb_Single())
    {
        m_type = basedata::HandType::Hand_Bomb_Single;
        m_point = m_fourCard[0];
    }
    else if(Hand_Bomb_Pair())
    {
        m_type = basedata::HandType::Hand_Bomb_Pair;
        m_point = m_fourCard[0];
    }
    else if(Hand_Bomb_Two_Single())
    {
        m_type = basedata::HandType::Hand_Bomb_Two_Single;
        m_point = m_fourCard[0];
    }
    else if(Hand_Bomb_Joker())
    {
        m_type = basedata::HandType::Hand_Bomb_Jokers;
    }
    else if(Hand_Bomb_Jokers_Single())
    {
        m_type = basedata::HandType::Hand_Bomb_Jokers_Single;
    }
    else if(Hand_Bomb_Jokers_Pair())
    {
        m_type = basedata::HandType::Hand_Bomb_Jokers_Pair;
    }
    else if(Hand_Bomb_Jokers_Two_Single())
    {
        m_type = basedata::HandType::Hand_Bomb_Jokers_Two_Single;
    }
}

bool PlayHand::Hand_Pass()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty()) return true;
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
    if(m_oneCard.isEmpty() && m_twoCard.size() > 2
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_twoCard.begin(),m_twoCard.end());
        if((static_cast<int>(m_twoCard.last()) - static_cast<int>(m_twoCard.first()) == m_twoCard.size() - 1)
            && m_twoCard.last() < basedata::CardPoint::Card_2
            && m_twoCard.first()>= basedata::CardPoint::Card_3) return true;
        else return false;
    }
 return false;
}

bool PlayHand::Hand_Seq_Single()
{
    if(m_oneCard.size() >4 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(),m_oneCard.end());
        if((static_cast<int>(m_oneCard.last()) - static_cast<int>(m_oneCard.first()) == m_oneCard.size() - 1)
            && m_oneCard.last() < basedata::CardPoint::Card_2
            && m_oneCard.first()>= basedata::CardPoint::Card_3) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Bomb()
{

    if(m_oneCard.isEmpty() && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.size() == 1) return true;
    return false;
}

bool PlayHand::Hand_Bomb_Single()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.size() == 1) return true;
    return false;
}

bool PlayHand::Hand_Bomb_Pair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1
        &&m_threeCard.isEmpty() && m_fourCard.size() == 1) return true;
    return false;
}

bool PlayHand::Hand_Bomb_Two_Single()
{
    if(m_oneCard.size() == 2 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.size() == 1)
    {
        std::sort(m_oneCard.begin(),m_oneCard.end());
        if(m_oneCard[0] != basedata::CardPoint::Card_SJ
            &&m_oneCard[1] != basedata::CardPoint::Card_BJ) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Bomb_Joker()
{
    if(m_oneCard.size() == 2 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(),m_oneCard.end());
        if(m_oneCard[0] == basedata::CardPoint::Card_SJ
            &&m_oneCard[1] == basedata::CardPoint::Card_BJ) return true;
        else return false;
    }
 return false;
}

bool PlayHand::Hand_Bomb_Jokers_Single()
{
    if(m_oneCard.size() == 3 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(),m_oneCard.end());
        if(m_oneCard[1] == basedata::CardPoint::Card_SJ
            &&m_oneCard[2] == basedata::CardPoint::Card_BJ) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Bomb_Jokers_Pair()
{
    if(m_oneCard.size() == 2 && m_twoCard.size() == 1
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(),m_oneCard.end());
        if(m_oneCard[0] == basedata::CardPoint::Card_SJ
            &&m_oneCard[1] == basedata::CardPoint::Card_BJ) return true;
        else return false;
    }
    return false;
}

bool PlayHand::Hand_Bomb_Jokers_Two_Single()
{
    if(m_oneCard.size() == 4 && m_twoCard.isEmpty()
        &&m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(),m_oneCard.end());
        if(m_oneCard[2] == basedata::CardPoint::Card_SJ
            &&m_oneCard[3] == basedata::CardPoint::Card_BJ) return true;
        else return false;
    }
    return false;
}

int PlayHand::getExtra()
{
    return m_cardsNum;
}

bool PlayHand::canBeat(const PlayHand &other)
{
    if(m_type ==basedata::HandType::Hand_Unknown) return false;
    if(other.m_type == basedata::HandType::Hand_Pass) return true;
    if(m_type == basedata::HandType::Hand_Bomb_Jokers) return true;
    if(m_type == basedata::HandType::Hand_Bomb && other.m_type >=basedata::HandType::Hand_Single
        && other.m_type <=basedata::HandType::Hand_Seq_Single) return true;
    if(m_type == other.m_type)
    {
        if(m_type == basedata::HandType::Hand_Seq_Pair ||  m_type == basedata::HandType::Hand_Seq_Single)
        {
            return m_point > other.m_point && m_cardsNum == other.m_cardsNum;
        }
        else
        {
            return m_point > other.m_point;
        }
    }
    return false;
}

CardPoint PlayHand::getCardPoint()
{
    return m_point;
}

HandType PlayHand::getHandType()
{
    return m_type;
}


