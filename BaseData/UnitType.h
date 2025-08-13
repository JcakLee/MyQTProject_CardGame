#ifndef UNITTYPE_H
#define UNITTYPE_H

namespace basedata
{
    //卡牌花色
    enum class CardSuit
    {
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };

    //卡牌点数
    enum class CardPoint
    {
        CardPoint_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,
        Card_BJ,
        CardPoint_End,
    };

} //end of namespace basedata




#endif // UNITTYPE_H

