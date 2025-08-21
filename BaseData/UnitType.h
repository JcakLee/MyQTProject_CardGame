#ifndef UNITTYPE_H
#define UNITTYPE_H

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

} //end of namespace basedata




#endif // UNITTYPE_H

