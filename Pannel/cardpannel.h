#ifndef CARDPANNEL_H
#define CARDPANNEL_H
#include "Pannel.h"
#include <QWidget>
#include "card.h"
#include "player.h"

using namespace basedata;

namespace pannel
{
    class EXPORT_PANNEL_ABI CardPannel : public QWidget
    {
        Q_OBJECT
    public:
        explicit CardPannel(QWidget *parent = nullptr);

        //设置卡牌图片
        void setImage(QPixmap& front, QPixmap& back);

        //获取卡牌图片
        QPixmap getImage();

        //设置卡牌显示哪一面
        void setFrontSide(bool flag);
        bool getFrontSide();

        //设置卡牌是否被选中
        void setIsSelected(bool flag);
        bool getIsSelected();

        //设置卡牌的点数以及花色
        void setCard(Card& card);
        Card getCard();

        //设置卡牌所有者
        void setOwner(Player* player);
        Player* getPlayer();

    signals:

    protected:
        //绘图事件
        void paintEvent(QPaintEvent* event);
        //鼠标点击事件
        void mousePressEvent(QMouseEvent* event);
    private:
        //图片信息
        QPixmap m_front;                 //图片正面
        QPixmap m_back;                  //图片反面
        bool m_isFront = true;           //标记卡牌正反面，默认为正面
        bool m_isSelected = false;       //标记卡牌是否被鼠标选择
        Card m_card;
        Player* m_player= nullptr;
    };
} // end of namespace pannel


#endif // CARDPANNEL_H
