#include "cardpannel.h"
#include <QPainter>
#include "UnitType.h"

namespace pannel
{
    CardPannel::CardPannel(QWidget *parent)
        : QWidget{parent}
    {

    }

    void CardPannel::setImage(QPixmap& front, QPixmap& back)
    {
        m_front = front;
        m_back = back;
        setFixedSize(m_front.size());
        update();
    }

    QPixmap CardPannel::getImage()
    {
        return m_front;
    }

    void CardPannel::setFrontSide(bool flag)
    {
        m_isFront = flag;
    }

    bool CardPannel::getFrontSide()
    {
        return m_isFront;
    }

    void CardPannel::setIsSelected(bool flag)
    {
        m_isSelected = flag;
    }

    bool CardPannel::getIsSelected()
    {
        return m_isSelected;
    }

    void CardPannel::setCard(Card& card)
    {
        m_card = card;
    }

    Card CardPannel::getCard()
    {
        return m_card;
    }

    void CardPannel::setOwner(Player *player)
    {
        m_player = player;
    }

    Player* CardPannel::getPlayer()
    {
        return m_player;
    }

    //update()执行后自动被框架调用
    void CardPannel::paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        if(m_isFront) painter.drawPixmap(rect(),m_front);
        else painter.drawPixmap(rect(),m_back);
    }

    void CardPannel::mousePressEvent(QMouseEvent *event)
    {

    }




} // end of namespace pannel


