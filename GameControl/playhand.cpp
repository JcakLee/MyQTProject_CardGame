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
    int num = static_cast<int>(basedata::CardPoint::CardPoint_End) - static_cast<int>(basedata::CardPoint::CardPoint_Begin);
    int cardRecord[num];
    memset(cardRecord,0,sizeof(int)*num);
    for(int i =0;i < list.size();++i)
    {
        Card card = list.at(i);


    }
}

void PlayHand::judgeCardType()
{

}


