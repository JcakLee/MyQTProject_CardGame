#ifndef UNITTYPE_H
#define UNITTYPE_H

//#include "UnitType.h"
#include <QHash>
#include <QtCore>

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
    /*内联函数：强枚举类型不能直接进行，不能隐式转换为整数， 不能直接进行算术运算，即 + 或者++操作，*/
    inline CardPoint operator+(CardPoint point, int value) {
        return static_cast<CardPoint>(static_cast<int>(point) + value);
    }

    inline CardPoint operator++(CardPoint& point) {
        return point = static_cast<CardPoint>(static_cast<int>(point) + 1);
    }

    inline CardSuit operator+(CardSuit suit, int value) {
        return static_cast<CardSuit>(static_cast<int>(suit) + value);
    }

    inline CardSuit operator++(CardSuit& suit) {
        return suit = static_cast<CardSuit>(static_cast<int>(suit) + 1);
    }

    //排序方式
    enum class SortType
    {
        ASC,
        DESC,
        NOSORT,
    };

    //玩家
    enum class Role
    {
        Lord,
        Farmer,
    };

    enum class Sex
    {
        Man,
        Woman,
    };

    enum class PlayerDir
    {
        Left,
        Right,
    };

    enum class PlayerType
    {
        Robot,
        User,
        Other,
    };

    //游戏状态
    enum class GameStatus
    {
        Dispatchcard,//发牌
        CallingLord,//叫地主
        PlayingHand,//出牌
    };

    //玩家状态
    enum class PlayerStatus
    {
        ThinkingForcallLord,//考虑抢地主
        ThinkingForPlayHand,//考虑出牌
        Winning,//出牌
    };


    // ----------------------------
    // 必须添加的哈希函数（针对枚举）
    // ----------------------------

    // CardSuit 的哈希函数
    inline size_t  qHash(CardSuit suit, size_t  seed = 0) noexcept
    {
        return ::qHash(static_cast<size_t >(suit), seed);
    }

    // CardPoint 的哈希函数
    inline size_t  qHash(CardPoint point, size_t  seed = 0) noexcept
    {
        return ::qHash(static_cast<size_t >(point), seed);
    }

    enum class Panel
    {
        Start,
        PlayCard,
        PassOrPlay,
        CallLord,
        Empty,
    };

    //牌型
    enum class HandType
    {
        Hand_Unknown,
        Hand_Pass,
        Hand_Single,
        Hand_Pair,
        Hand_Triple,
        Hand_Triple_Single,
        Hand_Triple_Pair,
        Hand_Plane,
        Hand_Plane_Two_Single,
        Hand_Plane_Pair,
        Hand_Seq_Pair,
        Hand_Seq_Single,
        Hand_Bomb,
        Hand_Bomb_Single,
        Hand_Bomb_Pair,
        Hand_Bomb_Two_Single,
        Hand_Bomb_Jokers,
        Hand_Bomb_Jokers_Single,
        Hand_Bomb_Jokers_Pair,
        Hand_Bomb_Jokers_Two_Single
    };

} //end of namespace basedata




#endif // UNITTYPE_H

